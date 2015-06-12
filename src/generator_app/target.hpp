/**
 *  \file       target.hpp
 *  \details    This file contains target class
 *  \author     Michal Zakowski, Jan Kumor
 */
#ifndef _TARGET_HPP
#define _TARGET_HPP
#include <vector>
#include <memory>

#include <cereal/cereal.hpp>

#include "curves/curve.hpp"
#include "curves/curve_factory.hpp"
#include "curves/curve_prototype.hpp"

#include "sensor_observer.hpp"

namespace generator_app {

class sensor_observer;
typedef std::shared_ptr<sensor_observer> p_sensor_observer;

/**
 * \brief representation of target
 *
 * Represents targets that change position during simulation, it moves along a given curve.
 */
class target : public std::enable_shared_from_this<target> {
public:
    /**
     * \defcon
     *
     * Automatically sets id_ and increments main id counter of targets.
     */
    target() : id_(gId_++){};
    /**
     * \brief create target from given data
     *
     * Automatically sets id_ and increments main id counter of targets.
     * \param curve given curve
     * \param initial_position given initial position of target in 3D space
     */
    target(curves::p_curve curve, commons::vect3f initial_position = commons::vect3f()) :curve_(curve), initial_position_(initial_position), current_position_(initial_position), id_(gId_++) {}
    /**
     * \defdtr
     */
    virtual ~target();
    /**
     * \brief update state.
     *
     * Updates target's position and notifies all observers to let them notice target's position change.
     * \param time moment for which target's state will be computed.
     */
    void update(float time);
    /**
     * \brief set observers of target
     *
     * Sets a pointer to vector to all observers available in current simulation.
     * \param observers smart pointer to vector of observers
     */
    void set_sensor_observers(std::shared_ptr<std::vector<p_sensor_observer> > observers);
    /**
     * \brief extract target's current position
     *
     * \return this current position in 3D space
     */
    commons::vect3f get_current_position() const;
    /**
     * \brief extract target's initial position
     *
     * \return this initial position in 3D space
     */
    commons::vect3f get_initial_position() const;
    /**
     * \getter{id_}
     */
    unsigned get_id() const;
    /**
     * \getter{curve_}
     */
    curves::p_curve get_curve() const { return curve_; }
    /**
     * \cerealbrief_save
     *
     * \cerealdoc_save{
     * - initial_position_ as "initial_position" nvp\n
     * - curve_prototype from curve_ as "curve" nvp\n
     * }
     */
    template <class Archive>
    void save( Archive& archiver ) const
    {
        archiver(
                cereal::make_nvp("initial_position", initial_position_),
                cereal::make_nvp("curve", curve_->proto() )
        );
    };
    /**
     * \cerealbrief_load
     *
     * \cerealdoc_load{
     * - initial_position_ as "initial_position" nvp\n
     * - curve_prototype as "curve" nvp which is later used to set curve_\n
     * }
     */
    template <class Archive>
    void load( Archive& archiver )
    {
        curves::curve_prototype cp;
        archiver(
                cereal::make_nvp("initial_position", initial_position_),
                cereal::make_nvp("curve", cp )
        );
        curve_ = curves::curve_factory::get_instance().create(cp);
    };
private:
    void notify();

    static unsigned gId_;
    unsigned id_;
    commons::vect3f initial_position_;
    commons::vect3f current_position_;
    curves::p_curve curve_;
    std::shared_ptr<std::vector<p_sensor_observer> > observers_;
};
/**
 * \brief Abbreviation for std::shared_ptr<\ref target>
 */
typedef std::shared_ptr<target> p_target;
/**
 * \brief Proxy to target class allowing loading from JSON format.
 */
class target_load_proxy {
public:
    /**
     * \defctr
     */
    target_load_proxy() {}
    /**
     * \brief creates proxy to pointed \ref target
     *
     * \param real smart pointer to object which will be proxied
     */
    target_load_proxy(p_target real) : real_(real) {}
    /**
     * \brief get pointer to proxied \ref target
     *
     * \return smart pointer to \ref target which is proxied by this
     */
    p_target get_real() const { return real_; }
    /**
     * \cerealbrief_save
     *
     * \cerealdoc_save{
     * - proxied object as "target" nvp\n
     * }
     */
    template<class Archive>
    void save(Archive& archive) const
    {
        archive(
                cereal::make_nvp("target", *real_)
        );
    }
    /**
     * \cerealbrief_save
     *
     * \cerealdoc_save{
     * - new proxied object as "target" nvp\n
     * }
     * Existing pointer will be override.
     */
    template<class Archive>
    void load(Archive& archive)
    {
        real_.reset();
        real_ = p_target( new target() );
        archive(
                cereal::make_nvp("target", *real_)
        );
    }

private:
    p_target real_;
};
}
#endif
