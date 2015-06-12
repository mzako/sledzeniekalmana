/**
 *  \file     filter_module.hpp
 *  \details   This file contains filter_module class
 *  \author    Michal Zakowski
 */
#ifndef _FILTER_MODULE_HPP
#define _FILTER_MODULE_HPP

#include <memory>
#include <queue>
#include <utility>
#include <vector>

#include "../commons/sensor_parameters_dto.hpp"
#include "../network/blocking_queue.hpp"
#include "../network/sending_buffer.hpp"

#include "../commons/vect3f.hpp"
#include "../commons/sensor_dto.hpp"
#include "kalman_filter.hpp"

namespace filter_app {
/**
 * \brief filter module main class
 *
 * Manages whole filter module. Realised as singleton pattern.
 */
class filter_module {
public:
    /**
     * \brief get the instance of singleton class
     *
     * \return smart pointer to filter module singleton instance
     */
    static std::shared_ptr<filter_module> get_instance() {
        if (!instance_) {
            instance_ = std::shared_ptr<filter_module>(new filter_module);
        }
        return instance_;
    }
    /**
     * \brief run function, prepares kalman filter to use and starts main loop
     *
     * \param blocking_queue represents data being received from generator module
     * \param sending_buf represents data being sent to comparator module
     */
    void run(std::shared_ptr<network::blocking_queue> blocking_queue,
            std::shared_ptr<network::sending_buffer> sending_buf);
    /**
     * \brief prepares kalman filter by setting targets
     *
     * \sa void filter_module::prepare_kalman_filter()
     */
    void prepare_kalman_filter();
    /**
     * \brief stops filter module, unlocks blocking queue if blocked
     *
     * \param queue blocking queue to unlock
     */
    void stop(std::shared_ptr<network::blocking_queue> queue);
private:
    filter_module()
            : is_started_(true) {
    }
    filter_module(const filter_module &) = delete;
    filter_module & operator=(const filter_module &) = delete;
    static std::shared_ptr<filter_module> instance_;

    std::vector<commons::sensor_parameters_dto> sensor_parameters_;
    std::vector<commons::sensor_dto> sensors_measurements_;
    std::string target_data_;
    std::unique_ptr<kalman_filter> kalman_filter_;
    volatile bool is_started_;

    void initialize_sensor_data(
            std::shared_ptr<network::blocking_queue> blocking_queue);
    void initialize_target_data(
            std::shared_ptr<network::blocking_queue> blocking_queue);
    void work(const std::shared_ptr<network::blocking_queue> blocking_queue,
            std::shared_ptr<network::sending_buffer>);
    void send_data_to_comparator(std::shared_ptr<network::sending_buffer>);
};
}

#endif //_FILTER_MODULE_HPP
