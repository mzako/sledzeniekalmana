/**
 *  \brief     filter_module.cpp
 *  \details   This file contains comparator_module class' functions definitions
 *  \author    Adam Mościcki
 */

#include "comparator_module.hpp"

using namespace std;
using namespace network;

namespace comparator_app {

std::shared_ptr<comparator_module>  comparator_module::instance_;

void comparator_module::run(std::shared_ptr<blocking_queue> compartaor_queue, std::shared_ptr<blocking_queue> filter_queue)
{
    while(is_started_) {

    }

}

void comparator_module::stop(std::shared_ptr<blocking_queue> compartaor_queue, std::shared_ptr<blocking_queue> filter_queue)
{
    is_started_ = false;
}

}
