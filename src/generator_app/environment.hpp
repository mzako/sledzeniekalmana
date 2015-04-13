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
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
namespace generator_app {
    /**
    * Class environment
    * Represents simulation world, contains objects and sensors
    */
    class environment {
    public:
        void update(unsigned);
        std::map<unsigned, vect3f> getPositions() const;
        void set_sensors(boost::shared_ptr<std::vector<boost::shared_ptr<sensor_observer>>>);
        void set_targets(boost::shared_ptr<std::vector<boost::shared_ptr<target>>>);
    private:
        boost::shared_ptr<std::vector<boost::shared_ptr<sensor_observer>>> sensors_;
        boost::shared_ptr<std::vector<boost::shared_ptr<target>>> targets_;
    };
}
#endif