/**
*  \brief     environment.cpp
*  \details   This file contains environment class' functions definitions
*  \author    Michal Zakowski
*/
#include <vector>
#include <memory>
#include "environment.hpp"
using namespace std;
using namespace generator_app;
/**
* Function set_sensors
* Sets sensors
*/
void environment::set_sensors(std::shared_ptr<vector<std::shared_ptr<sensor_observer>>> sensors)
{
    sensors_ = sensors;
}
/**
* Function set_sensors
* Sets targets
*/
void environment::set_targets(std::shared_ptr<vector<std::shared_ptr<target>>> targets)
{
    targets_ = targets;
}
/**
* Function update
* Updates all targets in simulation
*/
void environment::update(float time)
{
    vector<std::shared_ptr<target>>::iterator it;
    for (it = targets_->begin(); it != targets_->end(); ++it){
        (*it)->update(time);
    }
}
