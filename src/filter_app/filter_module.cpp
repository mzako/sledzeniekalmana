/**
 *  \file     filter_module.cpp
 *  \details   This file contains filter_module class' functions definitions
 *  \author    Michal Zakowski, Jan Kumor
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

#include "../commons/cout_writer.hpp"
#include "../commons/vect3f.hpp"
#include "../commons/measurement_dto.hpp"
#include "../commons/sensor_dto.hpp"

using namespace std;
using namespace network;
using namespace commons;

namespace filter_app {

std::shared_ptr<filter_module> filter_module::instance_;

void filter_module::prepare_kalman_filter() {
    kalman_filter_.reset(new kalman_filter);
    vector<pair<int, vect3f>> initial_positions;
    for (auto it = sensors_measurements_.begin();
            it != sensors_measurements_.end(); ++it) {
        vector<measurement_dto> tmp_meas = it->get_measurements();
        for (auto it2 = tmp_meas.begin(); it2 != tmp_meas.end(); ++it2) {
            initial_positions.push_back(
                    pair<int, vect3f>(it->get_id(), it2->point_));
        }
    }
    kalman_filter_->init_targets(initial_positions, sensor_parameters_);
}
void filter_module::run(std::shared_ptr<blocking_queue> blocking_queue,
        std::shared_ptr<network::sending_buffer> sending_buf) {
    if (!is_started_) {
        return;
    }
    initialize_sensor_data(blocking_queue);
    if (!is_started_) {
        return;
    }
    initialize_target_data(blocking_queue);
    prepare_kalman_filter();

    work(blocking_queue, sending_buf);
}

void filter_module::initialize_sensor_data(
        std::shared_ptr<blocking_queue> blocking_queue) {
    std::string initial_data = blocking_queue->pop();
#ifdef DEBUG
    cout_writer() << "SENSOR_DATA\n" << initial_data << "END_DATA\n";
#endif
    if (!is_started_) {
        return;
    }
    stringstream ss(initial_data);
    {
        cereal::JSONInputArchive iarchive(ss);
        iarchive(sensor_parameters_);
    }
}

void filter_module::initialize_target_data(
        std::shared_ptr<blocking_queue> blocking_queue) {
    std::string first_target_data = blocking_queue->pop();
#ifdef DEBUG
    cout_writer() << "FIRST_TARGET_DATA\n" << first_target_data << "END_DATA\n";
#endif
    if (!is_started_) {
        return;
    }
    stringstream ss(first_target_data);
    {
        cereal::JSONInputArchive iarchive(ss);
        iarchive(sensors_measurements_);
    }
}

void filter_module::work(const std::shared_ptr<blocking_queue> blocking_queue,
        std::shared_ptr<network::sending_buffer> sending_buf) {
    while (is_started_) {
        target_data_ = blocking_queue->pop();
#ifdef DEBUG
        cout_writer() << "TARGET_DATA\n" << target_data_ << "END_DATA\n";
#endif
        stringstream ss(target_data_);
        {
            cereal::JSONInputArchive iarchive(ss);
            iarchive(sensors_measurements_);
        }
        std::vector<vect3f> new_positions;
        for (auto it = sensors_measurements_.begin();
                it != sensors_measurements_.end(); ++it) {
            vector<measurement_dto> tmp_meas = it->get_measurements();
            for (auto it2 = tmp_meas.begin(); it2 != tmp_meas.end(); ++it2) {
                new_positions.push_back(it2->point_);
            }
        }
        kalman_filter_->compute(new_positions);
        send_data_to_comparator(sending_buf);
    }
}
void filter_module::send_data_to_comparator(
        std::shared_ptr<network::sending_buffer> sending_buf) {
    stringstream ss;
    {
        cereal::JSONOutputArchive oarchive(ss);
        oarchive(
                cereal::make_nvp("filter_output",
                        kalman_filter_->get_current_positions()));
    }
#ifdef DEBUG
    cout_writer() << "SENDING DATA:\n" << ss.str() << "\nEND DATA\n";
#endif
    sending_buf->send(ss.str());
}

void filter_module::stop(std::shared_ptr<network::blocking_queue> queue) {
    is_started_ = false;
    queue->push(""); //unblock if where blocked
}

}
