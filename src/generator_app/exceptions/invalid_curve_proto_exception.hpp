/*
 * invalid_curve_proto_exception.hpp
 *
 *  Created on: Jun 5, 2015
 *      Author: Jan Kumor
 */

#ifndef _INVALID_CURVE_PROTO_EXCEPTION_HPP
#define _INVALID_CURVE_PROTO_EXCEPTION_HPP

#include <stdexcept>
#include <string>

#ifndef _MSC_VER
#define NOEXCEPT noexcept (true)
#else
#define NOEXCEPT
#endif

namespace generator_app {
namespace exceptions {

class invalid_curve_proto_exception: public std::runtime_error {
public:
    invalid_curve_proto_exception(std::string reason) :
        std::runtime_error(("Curve prototype is invalid: "+reason).c_str() ) {};
    virtual ~invalid_curve_proto_exception() NOEXCEPT {};
};

} /* namespace exceptions */
} /* namespace generator_app */

#endif /* _INVALID_CURVE_PROTO_EXCEPTION_HPP */
