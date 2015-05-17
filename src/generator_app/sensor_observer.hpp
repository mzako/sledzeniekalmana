/**
*  \brief     sensor_observer.hpp
*  \details   This file contains sensor_observer class
*  \author    Michal Zakowski
*/

#ifndef SENSOROBSERVER_HPP
#define SENSOROBSERVER_HPP
#include <map>
#include <list>
#include "target.hpp"
#include "vect3f.hpp"
namespace generator_app {
    class target;
    /**
    * Class sensor_observer
    * Represents sensor gathering data about objects' position during simulation
    */
    class sensor_observer {
    public:
        sensor_observer(vect3f position = vect3f(), float radius = 0.f, float deviation = 0.f) : position_(position), radius_(radius), deviation_(deviation) {}
        void update(target const*);
        std::map<unsigned, vect3f> get_positions() const;
    private:
        vect3f make_noise(target const*) const;

        std::list<target const*> targets_;
        float deviation_;
        vect3f position_;
        float radius_;
    };
}
#endif