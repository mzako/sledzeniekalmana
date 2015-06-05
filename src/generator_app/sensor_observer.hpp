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
#include <cereal/types/vector.hpp>
#include "measurement_dto.hpp"

#include "target.hpp"
#include "sensor_parameters_dto.hpp"
#include "vect3f.hpp"

namespace generator_app {
class target;
/**
 * Class sensor_observer
 * Represents sensor gathering data about objects' position during simulation
 */
class sensor_observer {
public:
    //sensor_observer();
    sensor_observer(vect3f position = vect3f(), float radius = 0.f, float measurement_noise = 1.f, float process_noise = 1.f) : position_(position), radius_(radius), measurement_noise_(measurement_noise), process_noise_(process_noise), id_(gId_++) {}
    void update(std::shared_ptr<target>);
    unsigned get_id() const { return id_; }
    float get_measurement_noise() const { return measurement_noise_; }
    float get_process_noise() const { return process_noise_; }
    sensor_parameters_dto get_parameters() const { return sensor_parameters_dto(id_, measurement_noise_, process_noise_); }
    std::list<std::shared_ptr<target>> get_targets() { return targets_; }
    std::vector<measurement_dto> get_measurements() { return measurements_; }


    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(
                cereal::make_nvp("id", id_),
                cereal::make_nvp("position", position_),
                cereal::make_nvp("radius", radius_),
                cereal::make_nvp("measurement_noise", measurement_noise_),
                cereal::make_nvp("process_noise", process_noise_)
        );
    }

private:
    static unsigned gId_;
    unsigned id_;
    vect3f position_;
    float radius_;
    float measurement_noise_;
    float process_noise_;

    std::vector<measurement_dto> measurements_;
    std::list<std::shared_ptr<target>> targets_;

    measurement_dto make_measurement(std::shared_ptr<target>) const;

};

typedef std::shared_ptr<sensor_observer> p_sensor_observer;

class sensor_load_proxy {
public:
    sensor_load_proxy() {}
    sensor_load_proxy(p_sensor_observer real) : real_(real) {}
    p_sensor_observer get_real() const { return real_; }

    template<class Archive>
    void save(Archive& archive) const
    {
        archive(
                cereal::make_nvp("sensor", *real_)
        );
    }

    template<class Archive>
    void load(Archive& archive)
    {
        real_.reset();
        real_ = p_sensor_observer( new sensor_observer() );
        archive(
                cereal::make_nvp("sensor", *real_)
        );
    }

private:
    p_sensor_observer real_;
};
}
#endif
