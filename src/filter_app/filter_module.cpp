#include "filter_module.hpp"

using namespace filter_app;

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
	filter_ = boost::shared_ptr<kalman_filter>(new kalman_filter);
}

void filter_module::run()
{
	while(true)
	{
		//Code hard to implement with mocking network module
		//1. Try to lock product_empty sempaphore or block
		//2. add new snapshot to kalman filter
		//3. estimate state
		//4. send_data 
	}
}


void filter_module::receive_data(std::vector<vect3f> point)
{
	//Get data (async receive_data) save data somewhere  into the buffer (adding protected by lock) and unlock product_empy semaphore
}

void filter_module::send_data()
{
	//invoke code generating json and sending it furher
}