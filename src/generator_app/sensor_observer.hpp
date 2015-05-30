/**
*  \brief     sensor_observer.hpp
*  \details   This file contains sensor_observer class
*  \author    Michal Zakowski
*/

#ifndef SENSOROBSERVER_HPP
#define SENSOROBSERVER_HPP
#include <map>
#include <list>

#include <cereal/cereal.hpp>
#include <cereal/types/list.hpp>

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
        sensor_observer();
        sensor_observer(vect3f position = vect3f(), float radius = 0.f, float mean = 0.f, float deviation = 1.f) : position_(position), radius_(radius), deviation_(deviation), id_(gId_++) {}
        void update(std::shared_ptr<target>);
        std::map<unsigned, vect3f> get_positions() const;

        template<class Archive>
        void serialize(Archive& archive)
        {
            archive(
                    cereal::make_nvp("id", id_),
                    cereal::make_nvp("targets", targets_)
            );
        }

    private:
        static unsigned gId_;
        unsigned id_;

        vect3f make_noise(std::shared_ptr<target>) const;

        std::list<std::shared_ptr<target>> targets_;
        float mean_;
        float deviation_;
        vect3f position_;
        float radius_;
    };
}
#endif
