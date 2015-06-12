/**
 *  \file     line.cpp
 *  \details   This file contains line class' functions definitions
 *  \author    Michal Zakowski
 */
#include "line.hpp"

using namespace commons;

namespace generator_app {
namespace curves {

vect3f line::get_position(float time) const {
    return vect3f(velocity_.x_ * time, velocity_.y_ * time, velocity_.z_ * time);
}

} /* namespace curve */
} /* namespace generator_app */
