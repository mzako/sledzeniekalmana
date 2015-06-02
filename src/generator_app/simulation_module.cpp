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

#include <cereal/types/polymorphic.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>

#include "simulation_module.hpp"
#include "line.hpp"
#include "balistic.hpp"
#include "target_prototype.hpp"

using namespace std;
using namespace network;

namespace generator_app {


const float simulation_module::FREQUENCY_ = 10.0;

simulation_module* simulation_module::instance_ = nullptr;
/**
 * Function prepare_environment
 * Prepares environment to simulation by setting targets and sensors. If it isn't first simulation, it deletes old environment
 */
void simulation_module::prepare_environment(std::shared_ptr<vector<std::shared_ptr<target>>> targets, std::shared_ptr<vector<std::shared_ptr<sensor_observer>>> sensors)
{
    environment_.reset(new environment);
    environment_->set_targets(targets);
    environment_->set_sensors(sensors);
}

void simulation_module::initialize_simulation(std::string init_file_path) {
    //TODO: Sensor initialization from file
    shared_ptr<sensor_observer> sensor1( new sensor_observer(vect3f(0, 0, 0), 100000.f, 0.f, 0.4f) );
    shared_ptr<vector<p_target> > targets( new vector<p_target>);
    shared_ptr<vector<shared_ptr<sensor_observer> > > sensors( new vector<shared_ptr<sensor_observer> > );
    sensors->push_back(sensor1);

    std::vector<target_prototype> prototypes;

    std::fstream fs;
    /*fs.open("test.json", std::fstream::out);
    {
        cereal::JSONOutputArchive oarchive(fs);
        oarchive(
                cereal::make_nvp( "prototypes", prototypes )
        );
    }
    fs.close();*/
    fs.open(init_file_path, std::fstream::in);
    {
        cereal::JSONInputArchive iarchive(fs);
        iarchive(
                prototypes
        );
    }
    fs.close();

    for( auto element : prototypes ) {
        p_target tar = element.get_target();
        tar->set_sensor_observers(sensors);
        targets->push_back(tar);
    }

    prepare_environment(targets, sensors);
}

/**
 * Function run
 * Runs main simulation thread
 */
void simulation_module::run(shared_ptr<sending_buffer> filter_sending_buf, shared_ptr<sending_buffer> comparator_sending_buf, std::string init_file_path)
{
    initialize_simulation(init_file_path);

    while(true)
    {
        //cout << time_ / FREQUENCY_ << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        sendDataToFilter(filter_sending_buf);
        sendDataToComparator(comparator_sending_buf);

        time_ += 1;
        environment_->update(float(time_ / FREQUENCY_));

    }
}

void simulation_module::sendDataToFilter(shared_ptr<sending_buffer> sending_buf) {
    stringstream ss;
    {
        cereal::JSONOutputArchive oarchive(ss);
        oarchive(
                cereal::make_nvp("sensors", environment_->get_measurements() )
        );
    }
#ifdef DEBUG
    cout << "SENDING DATA:\n" << ss.str() << "\nEND DATA" << endl;
#endif
    sending_buf->send(ss.str());
}

void simulation_module::sendDataToComparator(shared_ptr<sending_buffer> sending_buf) {
    stringstream ss;
    {
        cereal::JSONOutputArchive oarchive(ss);
        oarchive(
                cereal::make_nvp("sensors", environment_->get_positions() )
        );
    }
#ifdef DEBUG
    cout << "SENDING DATA:\n" << ss.str() << "\nEND DATA" << endl;
#endif
    sending_buf->send(ss.str());
}

} /* namespace generator_app */

