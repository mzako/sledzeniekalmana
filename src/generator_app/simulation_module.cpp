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
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>

#include "simulation_module.hpp"
#include "../client_server/sending_buffer.hpp"
#include "line.hpp"
#include "balistic.hpp"

using namespace std;

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

void simulation_module::initialize_simulation() {
    shared_ptr<curve> line1( new line( vect3f(1.f, 1.f, 1.f) ) );
    shared_ptr<balistic> balistic1( new balistic(vect3f(400.f, 80.f, 400.f), 1.1 ) );
    shared_ptr<target> target1( new target(line1) );
    shared_ptr<target> target2( new target(balistic1) );
    shared_ptr<sensor_observer> sensor1( new sensor_observer(vect3f(0, 0, 0), 100000.f, 0.f, 0.4f) );
    shared_ptr<vector<shared_ptr<target> > > targets( new vector<shared_ptr<target> >);
    shared_ptr<vector<shared_ptr<sensor_observer> > > sensors( new vector<shared_ptr<sensor_observer> > );
    targets->push_back(target1);
    targets->push_back(target2);
    sensors->push_back(sensor1);
    target1->set_sensor_observers(sensors);
    target2->set_sensor_observers(sensors);
    prepare_environment(targets, sensors);
}

/**
 * Function run
 * Runs main simulation thread
 */
void simulation_module::run(shared_ptr<sending_buffer> filter_sending_buf, shared_ptr<sending_buffer> comparator_sending_buf)
{
    initialize_simulation();

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

