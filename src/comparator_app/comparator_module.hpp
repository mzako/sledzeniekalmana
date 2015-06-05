/**
*  \brief     filter_module.hpp
*  \details   This file contains filter_module class
*  \author    Adam Mościcki
*/
#ifndef _COMPARATOR_MODULE_HPP
#define _COMPARATOR_MODULE_HPP

#include <memory>
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
#include "../network/blocking_queue.hpp"


namespace comparator_app
{
    /**
    * Class filter_module
    * Manages whole comparator_module
    */
    class comparator_module
    {
    public:
        /**
         * Returns an instance of comparator_module class
         */
        static std::shared_ptr<comparator_module> get_instance()
        {
            if (!instance_)
            {
                instance_ = std::shared_ptr<comparator_module>(new comparator_module);
            }
            return instance_;
        }
        /**
         * Starts comparating thread
         */
        void run(std::shared_ptr<network::blocking_queue>, std::shared_ptr<network::blocking_queue>);
        /**
         * Stops comparing thread
         */
        void stop(std::shared_ptr<network::blocking_queue>, std::shared_ptr<network::blocking_queue>);
    private:
        comparator_module() : is_started_(true){}
        comparator_module(const comparator_module &) = delete;
        comparator_module & operator=(const comparator_module &) = delete;
        static std::shared_ptr<comparator_module>  instance_;
        volatile bool is_started_;
    };
}

#endif //_FILTER_MODULE_HPP
