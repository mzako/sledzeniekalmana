/**
*  \brief     simulation_module.cpp
*  \details   This file contains simulation_module class' functions definitions
*  \author    Michal Zakowski
*/
#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>
#include <memory>
#include <sstream>

#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>

#include "simulation_module.hpp"
#include "line.hpp"
#include "balistic.hpp"
using namespace std;
using namespace generator_app;
const float simulation_module::FREQUENCY_ = 10.0;
simulation_module* simulation_module::instance_ = nullptr;
/**
* Function prepare_environment
* Prepares environment to simulation by setting targets and sensors. If it isn't first simulation, it deletes old environment
*/
void simulation_module::prepare_environment(std::shared_ptr<vector<std::shared_ptr<target>>> targets, std::shared_ptr<vector<std::shared_ptr<sensor_observer>>> sensors)
{
    environment_.reset(new environment);
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
    balistic * balistic1 = new balistic(vect3f(400.f, 80.f, 400.f),1.1);
    std::shared_ptr<target> target1 = std::shared_ptr<target>(new target(line1));
    std::shared_ptr<target> target2 = std::shared_ptr<target>(new target(balistic1));
    sensor_observer * sensor1 = new sensor_observer(vect3f(0,0,0), 100000.f, 0.f, 0.4f);
    vector<std::shared_ptr<target>> targets;
    vector<std::shared_ptr<sensor_observer>> sensors;
    targets.push_back(target1);
    targets.push_back(target2);
    sensors.push_back(std::shared_ptr<sensor_observer>(sensor1));
    target1->set_sensor_observers(std::shared_ptr<vector<std::shared_ptr<sensor_observer>>>(&sensors));
    target2->set_sensor_observers(std::shared_ptr<vector<std::shared_ptr<sensor_observer>>>(&sensors));

    prepare_environment(std::shared_ptr<vector<std::shared_ptr<target>>>(&targets), std::shared_ptr<vector<std::shared_ptr<sensor_observer>>>(&sensors));

    while (true){
        //cout << time_ / FREQUENCY_ << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        map<unsigned, vect3f> pos = environment_->getPositions();
        map<unsigned, vect3f>::const_iterator it;

        stringstream ss;

        {
            cereal::JSONOutputArchive oarchive(ss);
            oarchive(
                    cereal::make_nvp("sensors", *(environment_->getSensors()) )
            );//
        }

        cout << ss.str() << endl;

        for (it = pos.begin(); it != pos.end(); ++it) {
            cout << "id: " << (*it).first << " (" << (*it).second.x_ << "," << (*it).second.y_ << "," << (*it).second.z_ << ")" << endl;
        }
        time_ += 1;
        environment_->update(float(time_ / FREQUENCY_));

    }
}
