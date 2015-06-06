/**
 *  \brief     filter_module.hpp
 *  \details   This file contains filter_module class
 *  \author    Adam Mościcki
 */
#ifndef _COMPARATOR_MODULE_HPP
#define _COMPARATOR_MODULE_HPP

#include <memory>

#include "../network/blocking_queue.hpp"
#include "../commons/vect3f.hpp"
#include "../commons/measurement_dto.hpp"
#include "../commons/sensor_dto.hpp"

namespace comparator_app
{

/**
 * Class comparator_module
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

    std::vector<commons::vect3f> filter_output_;
    std::vector<commons::sensor_dto> measurements_;
    std::vector<commons::sensor_dto> positions_;
};
}

#endif //_FILTER_MODULE_HPP
