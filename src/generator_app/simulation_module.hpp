/**
 *  \file     simulation_module.hpp
 *  \details   This file contains simulation_module class
 *  \author    Michal Zakowski, Jan Kumor
 */
#ifndef _SIMULATION_MODULE_HPP
#define _SIMULATION_MODULE_HPP
#include <vector>
#include <fstream>
#include <memory>

#include "environment.hpp"
#include "target.hpp"
#include "sensor_observer.hpp"
#include "../network/sending_buffer.hpp"

namespace generator_app {
/**
 * \brief Simulation module main class
 *
 * Manages whole simulation module.
 */
class simulation_module {
public:
    /**
     * \brief simulation_module singleton class instance access
     *
     * \return smart pointer to instance of simulation_module
     */
    static std::shared_ptr<simulation_module> get_instance() {
        if (!instance_)
            instance_ = std::shared_ptr<simulation_module>(
                    new simulation_module);
        return instance_;
    }
    /**
     * \brief prepares and initialize simulation environment
     *
     * Prepares environment to simulation by setting targets and sensors.
     * If it isn't first simulation, it deletes old environment.
     * \param targets smart pointer to vector of all targets existing in simulation
     * \param sensors smart pointer to vector of all sensors existing in simulation
     */
    void prepare_environment(
            std::shared_ptr<std::vector<std::shared_ptr<target>>>targets, std::shared_ptr<std::vector<std::shared_ptr<sensor_observer>>> sensors);
            /**
             * \brief initialize simulation with data from given std::fstream
             *
             * \param init_file reference to file stream containing simulation data in JSON format
             * \return string containing initialization data about sensors parameters, which is used by servers as initial message
             */
            std::string initialize(std::fstream& init_file);
            /**
             * \brief Starts simulation module computation loop.
             *
             * \param filter_sending_buf smart pointer to buffer to which will be used to write data for filter module
             * \param comparator_sending_buf smart pointer to buffer to which will be used to write data for comparator module
             */
            void run(std::shared_ptr<network::sending_buffer> filter_sending_buf, std::shared_ptr<network::sending_buffer> comparator_sending_buf);
            /**
             * stops the simulation
             */
            void stop();
            /**
             * \brief Length of one step of simulation
             */
            const static float TIME_STEP_;
        private:
            simulation_module() : initialized_(false) {}
            simulation_module(const simulation_module&) = delete;
            simulation_module& operator=(const simulation_module&) = delete;
            std::string initial_message() const;
            void send_data_to_filter(std::shared_ptr<network::sending_buffer> sending_buf);
            void send_data_to_comparator(std::shared_ptr<network::sending_buffer> sending_buf);

            static std::shared_ptr<simulation_module> instance_;
            float time_;
            std::unique_ptr<environment> environment_;
            bool initialized_;
            volatile bool is_started_;
        };
    }
#endif
