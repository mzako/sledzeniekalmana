/*
 * curve_prototype.hpp
 *
 *  Created on: Jun 3, 2015
 *      Author: elohhim
 */

#ifndef CURVE_PROTOTYPE_HPP
#define CURVE_PROTOTYPE_HPP

#include <exception>
#include <map>
#include <memory>
#include <string>
#include <utility>

#include <cereal/cereal.hpp>
#include <cereal/types/map.hpp>

namespace generator_app {

class curve_prototype {
public:
    curve_prototype() {};
    virtual ~curve_prototype();

    std::string get_type() const { return type_; }
    void set_type(const std::string type) { type_ = type; }
    float find_attribute(std::string key);
    void insert_attribute(std::string key, float value);


    template<class Archive>
    void save(Archive& archive) const
    {
        archive(
                cereal::make_nvp("type", type_),
                cereal::make_nvp("attributes", attributes_)
        );
    }

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

} /* namespace generator_app */

#endif /* CURVE_PROTOTYPE_HPP */