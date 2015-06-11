/**
 *  \file       no_attribute_exception.hpp
 *  \details    This file contains no_attribute_exception class
 *  \author     Jan Kumor
 */

#ifndef NO_ATTRIBUTE_EXCEPTION_HPP
#define NO_ATTRIBUTE_EXCEPTION_HPP

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
 * \brief Exception raised when curve prototype load from file is lacking of needed attribute
 */
class no_attribute_exception: public std::runtime_error {
public:
    /**
     * \brief Creates no_attribute_exception with given raising reason.
     *
     * Calls std::runtime_error() passing "No attribute named: " concatenated with reason parameter.
     * \param reason which parameter is lacking
     */
    no_attribute_exception(std::string attribute_name) : std::runtime_error(std::string("No attribute named: ").append(attribute_name).c_str()) {};
    /**
     * \defdtr
     */
    virtual ~no_attribute_exception() NOEXCEPT {};
};

} /* namespace exceptions */
} /* namespace generator_app */

#endif /* NO_ATTRIBUTE_EXCEPTION */
