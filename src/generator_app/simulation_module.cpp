/**
*  \brief     simulation_module.cpp
*  \details   This file contains simulation_module class' functions definitions
*  \author    Michal Zakowski
*/
#include <iostream>
#include <cmath>
#include <windows.h>
#include "simulation_module.hpp"
#include "line.hpp"
using namespace std;
simulation_module* simulation_module::instance_ = nullptr;
/**
* Function prepare_environment
* Prepares environment to simulation by setting targets and sensors. If it isn't first simulation, it deletes old environment
*/
void simulation_module::prepare_environment(vector<target*> targets, vector<sensor_observer*> sensors)
{
    environment* tmp = environment_;
    environment_ = new environment;
    if (tmp){
        delete tmp;
    }
    environment_->set_targets(targets);
    environment_->set_sensors(sensors);
}
/**
* Function run
* Runs main simulation thread
*/
void simulation_module::run()
{
    curve * line1 = new line(vect3f(1.f,1.f,1.f));
    target * target1 = new target(line1);
    sensor_observer * sensor1 = new sensor_observer(vect3f(), 100.f, 0.1f);
    vector<target*> targets;
    vector<sensor_observer*> sensors;
    targets.push_back(target1);
    sensors.push_back(sensor1);
    target1->set_sensor_observers(&sensors);

    if (!environment_){
        prepare_environment(targets, sensors);
    }
    while (true){
        Sleep(1000);
        map<unsigned, vect3f> pos = environment_->getPositions();
        map<unsigned, vect3f>::const_iterator it;
        for (it = pos.begin(); it != pos.end(); ++it){
            cout << "id: " << (*it).first << " (" << (*it).second.x_ << "," << (*it).second.y_ << "," << (*it).second.z_ << ")" << endl;
        }
        time_ += 1;
        environment_->update(time_);
    }
}
