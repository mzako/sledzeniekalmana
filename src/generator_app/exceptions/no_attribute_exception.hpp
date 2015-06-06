/*
 * no_attribute_exception.hpp
 *
 *  Created on: Jun 5, 2015
 *      Author: Jan Kumor
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

class no_attribute_exception: public std::runtime_error {
public:
    no_attribute_exception(std::string attribute_name) : std::runtime_error(std::string("No attribute named: ").append(attribute_name).c_str()) {};
    virtual ~no_attribute_exception() NOEXCEPT {};
};

} /* namespace exceptions */
} /* namespace generator_app */

#endif /* NO_ATTRIBUTE_EXCEPTION */
