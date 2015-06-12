/**
 *  \file       invalid_curve_proto_exception.hpp
 *  \details    This file contains invalid_curve_proto_exception class
 *  \author     Jan Kumor
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
/**
 * \brief Exception raised when curve prototype load from file is invalid
 */
class invalid_curve_proto_exception : public std::runtime_error {
public:
    /**
     * \brief Creates invalid_curve_proto_exception with given raising reason.
     *
     * Calls std::runtime_error() passing "Curve prototype is invalid:" concatenated with reason parameter.
     * \param reason why curve prototype is invalid
     */
    invalid_curve_proto_exception(std::string reason)
            : std::runtime_error(
                    ("Curve prototype is invalid: " + reason).c_str()) {
    }
    ;
    /**
     * \deftr
     */
    virtual ~invalid_curve_proto_exception() NOEXCEPT {
    }
    ;
};

} /* namespace exceptions */
} /* namespace generator_app */

#endif /* _INVALID_CURVE_PROTO_EXCEPTION_HPP */
