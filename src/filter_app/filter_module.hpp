﻿/**
*  \brief     filter_module.hpp
*  \details   This file contains filter_module class
*  \author    Michal Zakowski
*/
#ifndef _FILTER_MODULE_HPP
#define _FILTER_MODULE_HPP

#include <memory>
#include <queue>
#include <utility>
#include <vector>

#include "vect3f.hpp"
#include "sensor.hpp"
#include "../network/blocking_queue.hpp"
#include "kalman_filter.hpp"
#include "../commons/sensor_parameters_dto.hpp"

namespace filter_app 
{
    /**
    * Class filter_module
    * Manages whole filter module
    */
    class filter_module
    {
    public:
        static std::shared_ptr<filter_module> get_instance()
        {
            if (!instance_)
            {
                instance_ = std::shared_ptr<filter_module>(new filter_module);
            }
            return instance_;
        }
        void run(std::shared_ptr<network::blocking_queue>);
        bool prepare_kalman_filter();
        void receive_data(std::vector<vect3f>, std::vector<std::pair<float, float>>);
        void send_data();
        /**
         * Stop the main loop
         */
        void stop(std::shared_ptr<network::blocking_queue>);
    private:
        filter_module() : is_started_(true) {}
        filter_module(const filter_module &) = delete;
        filter_module & operator=(const filter_module &) = delete;
        static std::shared_ptr<filter_module>  instance_;
        std::queue<std::vector<vect3f>> positions_queue_;
        std::vector<std::pair<float,float>> sensors_params_;

        std::vector<commons::sensor_parameters_dto> sensor_parameters_;
        std::vector<sensor> sensors_;
        std::unique_ptr<kalman_filter> kalman_filter_;
        volatile bool is_started_;
        void initialize_sensor_data(std::shared_ptr<network::blocking_queue> blocking_queue);
        void initialize_target_data(std::shared_ptr<network::blocking_queue> blocking_queue);
    };
}

#endif //_FILTER_MODULE_HPP
