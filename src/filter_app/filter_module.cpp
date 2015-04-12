#include "filter_module.hpp"


filter_module* filter_module::instance_ = nullptr;

filter_module* filter_module::get_instance()
{
    if (instance_ == nullptr){
        instance_ = new filter_module;
    }
    return instance_;
}

filter_module::filter_module()
{

}

void filter_module::run()
{

}


void filter_module::receive_data(std::vector<vect3f> point)
{

}

void filter_module::send_data()
{

}