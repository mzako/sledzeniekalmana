/*
 * curve_factory.hpp
 *
 *  Created on: Jun 3, 2015
 *      Author: Jan Kumor
 */

#ifndef CURVE_FACTORY_HPP
#define CURVE_FACTORY_HPP

#include <functional>
#include <map>
#include <string>

#include "curve.hpp"
#include "curve_prototype.hpp"

namespace generator_app {
namespace curves {

class curve_factory {
public:
    static curve_factory& get_instance();

    typedef std::function<p_curve(curve_prototype&)> create_curve_function;

    bool register_curve(std::string type, create_curve_function fun);

    p_curve create(curve_prototype& proto);

private:
    // singleton pattern functions
    curve_factory();
    virtual ~curve_factory();
    curve_factory(const curve_factory&) = delete;
    curve_factory& operator=(const curve_factory&) = delete;

    typedef std::map<std::string, create_curve_function> callbacks;
    callbacks callbacks_;

    static bool is_initialized_;
};

} /* namespace curve */
} /* namespace generator_app */

#endif /* CURVE_FACTORY_HPP */
