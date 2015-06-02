/*
 * curve_proto.hpp
 *
 *  Created on: Jun 3, 2015
 *      Author: elohhim
 */

#ifndef SRC_GENERATOR_APP_CURVE_PROTO_HPP_
#define SRC_GENERATOR_APP_CURVE_PROTO_HPP_

#include <exception>
#include <map>
#include <memory>
#include <string>
#include <utility>

#include <cereal/cereal.hpp>
#include <cereal/types/map.hpp>

namespace generator_app {

class curve_proto {
public:
    curve_proto() {};
    virtual ~curve_proto();

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

        /*for(auto it = attributes_.begin(); it != attributes_.end(); it++)
        {
            archive(
                    cereal::make_nvp(it->first, it->second)
            );
        }*/
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

typedef std::shared_ptr<curve_proto> p_curve_proto;

} /* namespace generator_app */

#endif /* SRC_GENERATOR_APP_CURVE_PROTO_HPP_ */
