/**
*  \brief     filter_module.cpp
*  \details   This file contains filter_module class' functions definitions
*  \author    Michal Zakowski
*/
#include "filter_module.hpp"
#include <map>
#include <thread>
#include <fstream>
using namespace std;
using namespace filter_app;

filter_module* filter_module::instance_ = nullptr;
/**
* Function prepare_kalman_filter
* Prepares kalman filter by calling init_targets function. Uses initial positions in queue and sensor parameters
*/
bool filter_module::prepare_kalman_filter(){
    kalman_filter_.reset(new kalman_filter);
    if (positions_queue_.empty())
    {
        return false;
    }
    vector<vect3f> tmp_positions = positions_queue_.front();
    positions_queue_.pop();
    kalman_filter_->init_targets(tmp_positions,sensors_params_);
    return true;
}
/**
* Function run
* Runs main filter thread
*/
void filter_module::run()
{
    sensors_params_.push_back(pair<float, float>(11040, 3000));
    while (!prepare_kalman_filter())
    {
        this_thread::sleep_for(chrono::milliseconds(1000));
    }  
	while(true)
	{
        while (positions_queue_.empty()){
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
        vector<vect3f> tmp_positions = positions_queue_.front();
        positions_queue_.pop();
        kalman_filter_->compute(tmp_positions);
        vector<vect3f> res = kalman_filter_->get_current_positions();
	}
}

void filter_module::receive_data(std::vector<vect3f> positions, std::vector<std::pair<float, float>> sensors_params)
{
    positions_queue_.push(positions);
    sensors_params = sensors_params_;
}

void filter_module::send_data()
{
}
