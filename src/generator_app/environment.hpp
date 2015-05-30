/**
*  \brief     environment.hpp
*  \details   This file contains environment class
*  \author    Michal Zakowski
*/

#ifndef _ENVIRONMENT_HPP
#define _ENVIRONMENT_HPP
#include <vector>
#include <map>

#include "target.hpp"
namespace generator_app {
    /**
    * Class environment
    * Represents simulation world, contains objects and sensors
    */
    class environment {
    public:
        void update(float);
        std::map<unsigned, vect3f> getPositions() const;
        void set_sensors(std::shared_ptr<std::vector<std::shared_ptr<sensor_observer>>>);
        void set_targets(std::shared_ptr<std::vector<std::shared_ptr<target>>>);

        std::shared_ptr<std::vector<std::shared_ptr<target>>> getSensors() const {
            return targets_;
        }

    private:
        std::shared_ptr<std::vector<std::shared_ptr<sensor_observer>>> sensors_;
        std::shared_ptr<std::vector<std::shared_ptr<target>>> targets_;
    };
}
#endif
