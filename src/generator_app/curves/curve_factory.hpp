/**
 *  \file       curve_factory.hpp
 *  \details    This file contains curve_factory class
 *  \author     Jan Kumor
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
/**
 * \brief factory for hierarchy of classes inherited from \ref curve
 *
 * Allows creation of polymorphic classes from \ref curve hierarchy.
 * Usage of singleton pattern.
 */
class curve_factory {
public:
    /**
     * \brief access to curve_factory instance
     *
     *  \return reference to instance of singleton
     */
    static curve_factory& get_instance();
    /**
     * \brief function type of creational methods
     */
    typedef std::function<p_curve(curve_prototype&)> create_curve_function;
    /**
     * \brief register curve type in factory
     *
     * \param type name of registered type
     * \param fun static function which creates new type
     */
    bool register_curve(std::string type, create_curve_function fun);
    /**
     * \brief create curve from given prototype
     *
     * Allows creation of specific curve basing on curve_prototype.
     * According to type attribute of prototype calls create method from
     * corresponding class. Class must be registered in factory before.
     *
     * \param proto reference to given prototype
     * \return smart pointer to created object from curve class hierarchy
     */
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
