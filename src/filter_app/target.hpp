#ifndef _TARGET_HPP
#define _TARGET_HPP

#include <cereal/cereal.hpp>

#include "vect3f.hpp"

namespace filter_app 
{

/**
 * \brief Class represents a real object observing by a track
 * \author Adam Moscicki
 */
class target
{
public:
    target();
    ~target();
    void set_point(const vect3f&);
    vect3f get_point() const;
    void set_id(int id);
    int get_id() const;

    template<class Archive>
    void serialize(Archive& archive) {
        archive(
                cereal::make_nvp("id", id_),
                cereal::make_nvp("position", point_)
        );
    }
private:
    vect3f point_;
    int id_;
};

}

#endif //_TARGET_HPP
