/**
 *  \brief     simulation_module.hpp
 *  \details   This file contains simulation_module class
 *  \author    Michal Zakowski
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
 * Class simulation_module
 * Manages whole simulation module
 */
class simulation_module {
public:
    static std::shared_ptr<simulation_module> get_instance() {
        if (!instance_)
            instance_ = std::shared_ptr<simulation_module>(new simulation_module);
        return instance_;
    }

    void prepare_environment(std::shared_ptr<std::vector<std::shared_ptr<target>>>, std::shared_ptr<std::vector<std::shared_ptr<sensor_observer>>>);

    std::string initialize(std::fstream& init_file);
    void run(std::shared_ptr<network::sending_buffer> filter_sending_buf, std::shared_ptr<network::sending_buffer> comparator_sending_buf);
    /**
     * stops the simulation
     */
    void stop();
    const static float TIME_STEP_;
private:
    simulation_module() : initialized_(false) {}
    simulation_module(const simulation_module&) = delete;
    simulation_module& operator=(const simulation_module&) = delete;
    std::string initial_message() const;
    void sendDataToFilter(std::shared_ptr<network::sending_buffer> sending_buf);
    void sendDataToComparator(std::shared_ptr<network::sending_buffer> sending_buf);


    static std::shared_ptr<simulation_module> instance_;
    float time_;
    std::unique_ptr<environment> environment_;
    bool initialized_;
    volatile bool is_started_;
};
}
#endif
