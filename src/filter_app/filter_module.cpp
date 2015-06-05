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
bool filter_module::prepare_kalman_filter(){
    kalman_filter_.reset(new kalman_filter);
    if (positions_queue_.empty())
    {
        return false;
    }
    vector<vect3f> tmp_positions = positions_queue_.front();
    positions_queue_.pop();
    kalman_filter_->init_targets(tmp_positions,sensors_params_);
    return true;
}
/**
 * Function run
 * Runs main filter thread
 */
void filter_module::run(std::shared_ptr<blocking_queue> blocking_queue)
{
    sensors_params_.push_back(pair<float, float>(11040, 3000));

    kalman_filter_.reset(new kalman_filter);
    initialize_sensor_data(blocking_queue);
    initialize_target_data(blocking_queue);
    while(true)
    {
        std::string first_target_data = blocking_queue->pop();
#ifdef DEBUG
        cout << "TARGET_DATA" << endl << first_target_data << endl;
#endif
        stringstream ss(first_target_data);
        {
            cereal::JSONInputArchive iarchive(ss);
            iarchive(
                    sensors_
            );
        }
        /*  while (positions_queue_.empty()){
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
        vector<vect3f> tmp_positions = positions_queue_.front();
        positions_queue_.pop();
        kalman_filter_->compute(tmp_positions);
        vector<vect3f> res = kalman_filter_->get_current_positions();*/
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
                sensors_
        );
    }
}

void filter_module::receive_data(std::vector<vect3f> positions, std::vector<std::pair<float, float>> sensors_params)
{
    positions_queue_.push(positions);
    sensors_params = sensors_params_;
}

void filter_module::send_data()
{
}

}
