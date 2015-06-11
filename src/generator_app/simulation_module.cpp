/**
 *  \brief     simulation_module.cpp
 *  \details   This file contains simulation_module class' functions definitions
 *  \author    Michal Zakowski
 */
#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>
#include <memory>
#include <sstream>
#include <fstream>

#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>

#include "../commons/sensor_parameters_dto.hpp"
#include "../commons/cout_writer.hpp"

#include "target.hpp"
#include "simulation_module.hpp"

using namespace std;
using namespace network;
using namespace commons;

namespace generator_app {

const float simulation_module::TIME_STEP_ = 1;

shared_ptr<simulation_module> simulation_module::instance_;
/**
 * Function prepare_environment
 * Prepares environment to simulation by setting targets and sensors. If it isn't first simulation, it deletes old environment
 */
void simulation_module::prepare_environment(std::shared_ptr<vector<std::shared_ptr<target>>> targets, std::shared_ptr<vector<std::shared_ptr<sensor_observer>>> sensors)
{
    environment_.reset(new environment);
    environment_->set_targets(targets);
    environment_->set_sensors(sensors);
    is_started_ = true;
}

string simulation_module::initialize(std::fstream& init_file) {
    shared_ptr<vector<p_target> > targets( new vector<p_target>);
    shared_ptr<vector<p_sensor_observer > > sensors( new vector<p_sensor_observer> );

    vector<sensor_load_proxy> sensor_proxies;
    vector<target_load_proxy> target_proxies;

    {
        cereal::JSONInputArchive iarchive(init_file);
        iarchive(
                target_proxies,
                sensor_proxies
        );
    }
    //populate sensors list
    for( auto element : sensor_proxies ) {
        sensors->push_back(element.get_real());
    }
    //populate targets list
    for( auto element : target_proxies ) {
        p_target tar = element.get_real();
        tar->set_sensor_observers(sensors);
        targets->push_back(tar);
    }

    prepare_environment(targets, sensors);
    time_ = 0;
    initialized_ = true;
    return initial_message();
}

/**
 * Function run
 * Runs main simulation thread
 */
void simulation_module::run(shared_ptr<sending_buffer> filter_sending_buf, shared_ptr<sending_buffer> comparator_sending_buf)
{
    if(initialized_) {
        while(is_started_)
        {
            environment_->update(float(time_));
            send_data_to_filter(filter_sending_buf);
            send_data_to_comparator(comparator_sending_buf);

            this_thread::sleep_for(chrono::milliseconds(1000));
            time_ += TIME_STEP_;
        }
    }
}

void simulation_module::stop()
{
    is_started_ = false;
}

string simulation_module::initial_message() const {
    vector<sensor_parameters_dto> parameters;
    for( auto sensor : *(environment_->get_sensors()) )
    {
        parameters.push_back(sensor->get_parameters() );
    }
    stringstream ss;
    {
        cereal::JSONOutputArchive oarchive(ss);
        oarchive(
                cereal::make_nvp("sensors_parameters", parameters)
        );

    }
#ifdef DEBUG
    cout_writer() << "SENDING DATA:\n" << ss.str() << "\nEND DATA\n";
#endif
    return ss.str();
}

void simulation_module::send_data_to_filter(shared_ptr<sending_buffer> sending_buf) {
    stringstream ss;
    {
        cereal::JSONOutputArchive oarchive(ss);
        oarchive(
                cereal::make_nvp("sensors_measurements", environment_->get_measurements() )
        );
    }
#ifdef DEBUG
    cout_writer() << "SENDING DATA:\n" << ss.str() << "\nEND DATA\n";
#endif
    sending_buf->send(ss.str());
}

void simulation_module::send_data_to_comparator(shared_ptr<sending_buffer> sending_buf) {
    stringstream ss;
    {
        cereal::JSONOutputArchive oarchive(ss);
        oarchive(
                //cereal::make_nvp("sensors_positions", environment_->get_positions() ),
                cereal::make_nvp("target_positions", environment_->get_positions2() ),
                cereal::make_nvp("sensors_measurments", environment_->get_measurements() )
        );
    }
#ifdef DEBUG
    cout_writer() << "SENDING DATA:\n" << ss.str() << "\nEND DATA\n";
#endif
    sending_buf->send(ss.str());
}

} /* namespace generator_app */

