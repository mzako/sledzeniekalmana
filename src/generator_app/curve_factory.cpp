/*
 * curve_factory.cpp
 *
 *  Created on: Jun 3, 2015
 *      Author: Jan Kumor
 */

#include "curve_factory.hpp"

#include <exception>
#include <utility>

#include "balistic.hpp"
#include "line.hpp"

namespace generator_app {

bool curve_factory::is_initialized_ = false;

curve_factory::curve_factory() {
    //Do nothing
}

curve_factory::~curve_factory() {
    //Do nothing
}

curve_factory& curve_factory::get_instance() {
    static curve_factory instance;
    if(!is_initialized_)
    {
        instance.register_curve("line", line::create);
        instance.register_curve("balistic", balistic::create);
        is_initialized_ = true;
    }
    return instance;
}

bool curve_factory::register_curve(std::string type, create_curve_function fun) {
    return ( callbacks_.insert( std::pair<std::string, create_curve_function>(type, fun) ) ).second;
}

p_curve curve_factory::create(curve_prototype& proto) {
    auto it = callbacks_.find(proto.get_type());
    if (it == callbacks_.end()) {
        throw( std::exception() );
    } else {
        return (it->second)(proto);
    }
}

} /* namespace generator_app */
