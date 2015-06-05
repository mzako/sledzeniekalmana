/*
 * target_prototype.hpp
 *
 *  Created on: Jun 3, 2015
 *      Author: elohhim
 */

#ifndef TARGETPROTOTYPE_HPP
#define TARGETPROTOTYPE_HPP

#include <memory>

#include <cereal/cereal.hpp>

#include "target.hpp"
#include "vect3f.hpp"
#include "curve.hpp"
#include "curve_factory.hpp"

namespace generator_app {

class target_prototype {
public:
    friend class target;

    target_prototype() {};
    target_prototype(p_target target) {
        initial_position_ = target->get_initial_position();
        curve_proto_ = target->get_curve()->proto();
    }

    virtual ~target_prototype() {};

    p_target get_target() {
        return p_target(new target(curve_factory::get_instance().create( curve_proto_ ), initial_position_));
    }

    template <class Archive>
    void serialize( Archive& archiver )
    {
        archiver(
                cereal::make_nvp("initial_position", initial_position_),
                cereal::make_nvp("curve", curve_proto_)
        );
    };

private:
    vect3f initial_position_;
    curve_prototype curve_proto_;
};

} /* namespace generator_app */

#endif /* TARGETPROTOTYPE_HPP */
