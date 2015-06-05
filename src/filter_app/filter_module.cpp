/**
 *  \brief     filter_module.cpp
 *  \details   This file contains filter_module class' functions definitions
 *  \author    Michal Zakowski
 */

#include "filter_module.hpp"

#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include <utility>

#include <cereal/archives/json.hpp>
#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>

#include "sensor.hpp"

using namespace std;
using namespace network;

namespace filter_app {

std::shared_ptr<filter_module>  filter_module::instance_;
/**
 * Function prepare_kalman_filter
 * Prepares kalman filter by calling init_targets function. Uses initial positions in queue and sensor parameters
 */
void filter_module::prepare_kalman_filter(){
    kalman_filter_.reset(new kalman_filter);
    vector<pair<int,vect3f>> initial_positions;
    for (auto it = sensors_measurements_.begin(); it != sensors_measurements_.end(); ++it)
    {
        for (auto it2 = tmp_meas.begin(); it2 != tmp_meas.end(); ++it2)
        {
            initial_positions.push_back(pair<int,vect3f>(it->get_id(),it2->get_position()));
        }
    }
    kalman_filter_->init_targets(initial_positions, sensor_parameters_);


}
/**
 * Function run
 * Runs main filter thread
 */
void filter_module::run(std::shared_ptr<blocking_queue> blocking_queue)
{
    initialize_sensor_data(blocking_queue);
    initialize_target_data(blocking_queue);
    prepare_kalman_filter();

    while(true)
    {
        std::string first_target_data = blocking_queue->pop();
#ifdef DEBUG
        cout << "TARGET_DATA" << endl << first_target_data << endl;
#endif
        std::vector<vect3f> new_positions;
        stringstream ss(first_target_data);
        {
            cereal::JSONInputArchive iarchive(ss);
            iarchive(
                sensors_measurements_
            );
        }
        for (auto it = sensors_measurements_.begin(); it != sensors_measurements_.end(); ++it)
        {
            vector<measurement> tmp_meas = it->get_measurements();
            for (auto it2 = tmp_meas.begin(); it2 != tmp_meas.end(); ++it2)
            {
                new_positions.push_back(it2->get_position());
            }
        }
        kalman_filter_->compute(new_positions);
        vector<vect3f> res = kalman_filter_->get_current_positions();
    }
}
void filter_module::initialize_sensor_data(std::shared_ptr<blocking_queue> blocking_queue) {
    std::string initial_data = blocking_queue->pop();
#ifdef DEBUG
    cout << "SENSOR_DATA" << endl << initial_data << endl;
#endif
    stringstream ss(initial_data);
    {
        cereal::JSONInputArchive iarchive(ss);
        iarchive(
                sensor_parameters_
        );
    }
}

void filter_module::initialize_target_data(std::shared_ptr<blocking_queue> blocking_queue) {
    std::string first_target_data = blocking_queue->pop();
#ifdef DEBUG
    cout << "FIRST_TARGET_DATA" << endl << first_target_data << endl;
#endif
    stringstream ss(first_target_data);
    {
        cereal::JSONInputArchive iarchive(ss);
        iarchive(
                sensors_measurements_
        );
    }
}

void filter_module::send_data()
{
}

}
