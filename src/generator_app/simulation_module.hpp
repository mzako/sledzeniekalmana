/**
*  \brief     simulation_module.hpp
*  \details   This file contains simulation_module class
*  \author    Michal Zakowski
*/
#ifndef _SIMULATION_MODULE_HPP
#define _SIMULATION_MODULE_HPP
#include <vector>
#include "environment.hpp"
#include "target.hpp"
#include "sensor_observer.hpp"
#include "../client_server/sending_buffer.hpp"
namespace generator_app {
    /**
    * Class simulation_module
    * Manages whole simulation module
    */
    class simulation_module {
    public:
        static simulation_module* get_instance(){
            if (!instance_)
                instance_ = new simulation_module;
            return instance_;
        }
        void prepare_environment(std::shared_ptr<std::vector<std::shared_ptr<target>>>, std::shared_ptr<std::vector<std::shared_ptr<sensor_observer>>>);
        void run(std::shared_ptr<sending_buffer> filter_sending_buf, std::shared_ptr<sending_buffer> comparator_sending_buf);

        const static float FREQUENCY_;
    private:
        simulation_module(){}
        simulation_module(const simulation_module&) = delete;
        simulation_module& operator=(const simulation_module&) = delete;
        void sendDataToFilter(std::shared_ptr<sending_buffer> sending_buf);
        void sendDataToComparator(std::shared_ptr<sending_buffer> sending_buf);
        void initialize_simulation();

        static simulation_module* instance_;
        unsigned time_;
        std::unique_ptr<environment> environment_;
    };
}
#endif
