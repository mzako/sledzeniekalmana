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
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
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
        void prepare_environment(boost::shared_ptr<std::vector<boost::shared_ptr<target>>>, boost::shared_ptr<std::vector<boost::shared_ptr<sensor_observer>>>);
        void run();
    private:
        simulation_module(){}
        simulation_module(const simulation_module&) = delete;
        simulation_module& operator=(const simulation_module&) = delete;
        void sendData();
        void getData();

        static simulation_module* instance_;
        unsigned time_;
        boost::scoped_ptr<environment> environment_;
    };
}
#endif