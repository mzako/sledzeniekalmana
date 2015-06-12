/**
 *  \file     target.cpp
 *  \details   This file contains target class' functions definitions
 *  \author    Michal Zakowski
 */
#include <vector>
#include <memory>

#include "../commons/vect3f.hpp"

#include "target.hpp"

using namespace std;
using namespace commons;

namespace generator_app {

unsigned target::gId_ = 1;

target::~target() {
    //Do nothing
}

void target::update(float time) {
    current_position_ = curve_->get_position(time) + initial_position_;
    notify();
}
/**
 * Function notify
 * Notifies all observers by calling their update function
 */
void target::notify() {
    if (observers_) {
        for (auto it = observers_->begin(); it != observers_->end(); ++it) {
            (*it)->update(shared_from_this());
        }
    }
}

void target::set_sensor_observers(
        std::shared_ptr<vector<std::shared_ptr<sensor_observer>>> observers) {
    observers_ = observers;
}

vect3f target::get_current_position() const {
    return current_position_;
}

vect3f target::get_initial_position() const {
    return initial_position_;
}

unsigned target::get_id() const {
    return id_;
}

} /* namespace generator_app */
