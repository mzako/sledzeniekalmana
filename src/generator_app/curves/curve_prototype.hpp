/**
 *  \file       curve_prototype.hpp
 *  \details    This file contains curve_prototype class
 *  \author     Jan Kumor
 */

#ifndef _CURVE_PROTOTYPE_HPP
#define _CURVE_PROTOTYPE_HPP

#include <map>
#include <memory>
#include <string>

#include <cereal/cereal.hpp>
#include <cereal/types/map.hpp>

namespace generator_app {
namespace curves {
/**
 * \brief curve prototype for factory purposes
 *
 * This class allows file serialization of \ref curve based polymorphic classes.
 * Prototypes are input for \ref curve_factory create methods.
 */
class curve_prototype {
public:
    /**
     * \stdcon
     */
    curve_prototype();
    /**
     * \stddtr
     */
    virtual ~curve_prototype();
    /**
     * \getter{type_}
     */
    std::string get_type() const { return type_; }
    /**
     * \setter{type_}
     */
    void set_type(const std::string type) { type_ = type; }
    /**
     * \brief find attribute in attribute map
     *
     * Allows extraction of specific attribute from prototype.
     * May raise \ref no_attribute_exception if wanted attribute is lacking.
     *
     * \param key name of wanted attribute
     * \return value of attribute
     */
    float find_attribute(std::string key);
    /**
     * \brief insert attribure to attribute map
     *
     * Allows inserting specific attribute to prototype.
     *
     * \param key name of attribute
     * \param value value of attribute
     */
    void insert_attribute(std::string key, float value);
    /**
     * \cerealbrief_save
     *
     * \cerealdoc_save{
     * - #type_ as "type" nvp\n
     * - #attributes_ as "attributes" nvp\n
     * }
     */
    template<class Archive>
    void save(Archive& archive) const
    {
        archive(
                cereal::make_nvp("type", type_),
                cereal::make_nvp("attributes", attributes_)
        );
    }
    /**
     * \cerealbrief_load
     *
     * \cerealdoc_load{
     * - type_ as "type" nvp\n
     * - attributes_ as "attributes" nvp\n
     * }
     */
    template<class Archive>
    void load(Archive& archive)
    {
        archive(
                cereal::make_nvp("type", type_),
                cereal::make_nvp("attributes", attributes_)
        );
    }

private:
    std::string type_;
    std::map<std::string, float> attributes_;
};

typedef std::shared_ptr<curve_prototype> p_curve_prototype;

} /* namespace curve */
} /* namespace generator_app */

#endif /* _CURVE_PROTOTYPE_HPP */
