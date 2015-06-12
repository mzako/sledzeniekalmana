/**
 *  \file       curve_factory.cpp
 *  \details    This file contains curve_factory class' functions definitions
 *  \author     Jan Kumor
 */


#include "curve_factory.hpp"

#include <utility>

#include "../exceptions/invalid_curve_proto_exception.hpp"
#include "../exceptions/no_attribute_exception.hpp"
#include "balistic.hpp"
#include "line.hpp"

namespace generator_app {
namespace curves {

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
        throw( std::runtime_error((proto.get_type()+": no such curve type registered in factory.").c_str()) );
    } else {
        try
        {
            return (it->second)(proto);
        } catch (exceptions::no_attribute_exception& e) {
            throw exceptions::invalid_curve_proto_exception( e.what() );
        }

    }
}

} /* namespace curve */
} /* namespace generator_app */
