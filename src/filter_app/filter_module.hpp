/**
*  \brief     filter_module.hpp
*  \details   This file contains filter_module class
*  \author    Michal Zakowski
*/
#ifndef _FILTER_MODULE_HPP
#define _FILTER_MODULE_HPP

#include <vector>
#include <queue>
#include "vect3f.hpp"
#include "kalman_filter.hpp"

namespace filter_app 
{
    /**
    * Class filter_module
    * Manages whole filter module
    */
    class filter_module
    {
    public:
        static filter_module* get_instance()
        {
            if (instance_ == nullptr)
            {
                instance_ = new filter_module;
            }
            return instance_;
        }
        void run();
        bool prepare_kalman_filter();
        void filter_module::receive_data(std::vector<vect3f>, std::vector<std::pair<float, float>>);
        void filter_module::send_data();
    private:
        filter_module(){}
        filter_module(const filter_module &) = delete;
        filter_module & operator=(const filter_module &) = delete;
        static filter_module * instance_;
        std::queue<std::vector<vect3f>> positions_queue_;
        std::vector<std::pair<float,float>> sensors_params_;
        std::unique_ptr<kalman_filter> kalman_filter_;
    };
}

#endif //_FILTER_MODULE_HPP