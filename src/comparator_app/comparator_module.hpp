/**
 *  \file       comparator_module.hpp
 *  \details    This file contains comparator_module class
 *  \author     Adam Mościcki, Jan Kumor
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
     * \brief comparator_module singleton class instance access
     *
     * \return smart pointer to instance of comparator_module
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
     * \brief Starts comparator module computation loop.
     *
     * \param generator_queue pointer to blocking queue of \ref client listening for data from GeneratorModule
     * \param filter_queue pointer to blocking queue of \ref client listening for data from FilterModule
     */
    void run(std::shared_ptr<network::blocking_queue> generator_queue, std::shared_ptr<network::blocking_queue> filter_queue);
    /**
     * \brief Breaks comparato module computation loop.
     */
    void stop(std::shared_ptr<network::blocking_queue>, std::shared_ptr<network::blocking_queue>);
    
    
private:
    comparator_module() : is_started_(true){}
    comparator_module(const comparator_module &) = delete;
    comparator_module & operator=(const comparator_module &) = delete;
    static std::shared_ptr<comparator_module>  instance_;

    static const char sep_ = ',';
    static const char line_sep_ = ';';
    static const char set_sep_ = '#';
    volatile bool is_started_;

    std::vector<commons::vect3f> filter_output_;
    std::vector<commons::sensor_dto> measurements_;
    std::vector<commons::measurement_dto> positions2_;

    void get_filter_data(std::shared_ptr<network::blocking_queue> filter_queue);
    void get_generator_data(std::shared_ptr<network::blocking_queue> qenerator_queue);
    void real_plot_string(std::ostringstream& plot_stream);
    void meas_plot_string(std::ostringstream& plot_stream);
    void track_plot_string(std::ostringstream& plot_stream);
    void send_plot_data();
    /*
     * Counts cumulated error
     */
    double count_error();
};
}

#endif //_FILTER_MODULE_HPP
