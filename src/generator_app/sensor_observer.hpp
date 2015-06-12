/**
 *  \file     sensor_observer.hpp
 *  \details   This file contains sensor_observer class
 *  \author    Michal Zakowski, Jan Kumor
 */

#ifndef SENSOROBSERVER_HPP
#define SENSOROBSERVER_HPP
#include <map>
#include <list>

#include <cereal/cereal.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/vector.hpp>

#include "../commons/measurement_dto.hpp"
#include "../commons/sensor_parameters_dto.hpp"
#include "../commons/vect3f.hpp"

#include "target.hpp"

namespace generator_app {
class target;
/**
 * \brief Represents real  measuring sensor
 *
 * Represents sensor gathering data about objects' position during simulation
 * Designed as observer pattern
 *
 */
class sensor_observer {
public:

    /**
     *  \stdcon
     */
    sensor_observer(commons::vect3f position = commons::vect3f(), float radius = 0.f, float measurement_noise = 1.f, float process_noise = 1.f) : position_(position), radius_(radius), measurement_noise_(measurement_noise), process_noise_(process_noise), id_(gId_++) {}

    /**
     * \brief update targets positions
     *
     * Checks whether targets entered or left sensor's area and inserts or removes target from sensor's target list
     */
    void update(std::shared_ptr<target>);

    /**
     * \getter{id_}
     */
    unsigned get_id() const { return id_; }

    /**
     * \getter{measurement_noise_}
     */
    float get_measurement_noise() const { return measurement_noise_; }

    /**
     * \getter{process_noise_}
     *
     * Needed by Kalman filter to calculate how far we trust process
     */
    float get_process_noise() const { return process_noise_; }

    /**
     * \brief Encapsulate sensor parameter
     *
     * \sa {sensor_parametrs_dto}
     */
    commons::sensor_parameters_dto get_parameters() const {
        return commons::sensor_parameters_dto(id_, measurement_noise_, process_noise_, radius_, position_);
    }

    /**
     * \brief real targets posions
     *
     * Return real targets position
     */
    std::vector<commons::measurement_dto> get_positions() const;

    /**
     * \brief measure targets position
     *
     * Returns measurement which is target's position with noise
     */
    std::vector<commons::measurement_dto> get_measurements() const;

    /**
     * \brief serializing method
     *
     * Serialize template needed by Cereal to serialize sensor object
     */
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
    commons::vect3f position_;
    float radius_;
    float measurement_noise_;
    float process_noise_;

    std::vector<commons::measurement_dto> measurements_;
    std::list<std::shared_ptr<target>> targets_;

    commons::measurement_dto make_measurement(std::shared_ptr<target>) const;

};
/**
 * \brief Abbreviation for std::shared_ptr<\ref sensor_observer>
 */
typedef std::shared_ptr<sensor_observer> p_sensor_observer;
/**
 * \brief Proxy to sensor_observer class allowing loading from JSON format.
 */
class sensor_load_proxy {
public:
    /**
     * \defctr
     */
    sensor_load_proxy() {}
    /**
     * \brief creates proxy to pointed \ref sensor_observer
     *
     * \param real smart pointer to object which will be proxied
     */
    sensor_load_proxy(p_sensor_observer real) : real_(real) {}
    /**
     * \brief get pointer to proxied \ref sensor_observer
     *
     * \return smart pointer to \ref sensor_observer which is proxied by this
     */
    p_sensor_observer get_real() const { return real_; }
    /**
     * \cerealbrief_save
     *
     * \cerealdoc_save{
     * - proxied object as "sensor" nvp\n
     * }
     */
    template<class Archive>
    void save(Archive& archive) const
    {
        archive(
                cereal::make_nvp("sensor", *real_)
        );
    }
    /**
     * \cerealbrief_save
     *
     * \cerealdoc_save{
     * - new proxied object as "sensor" nvp\n
     * }
     * Existing pointer will be override.
     */
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
} /* namespace generator_app */
#endif
