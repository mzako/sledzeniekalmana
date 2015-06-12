/**
 *  \file       curve_prototype.cpp
 *  \details    This file contains curve_prototype class' functions definitions
 *  \author     Jan Kumor
 */

#include "curve_prototype.hpp"

#include "../exceptions/no_attribute_exception.hpp"

namespace generator_app {
namespace curves {

curve_prototype::curve_prototype() {
    //Do nothing
}

curve_prototype::~curve_prototype() {
    //Do nothing
}

float curve_prototype::find_attribute(std::string key) {
    std::map<std::string, float>::const_iterator it = attributes_.find(key);
    if( it == attributes_.end() )
    {
        throw( exceptions::no_attribute_exception(key) );
    } else {
        return it->second;
    }
}

void curve_prototype::insert_attribute(std::string key, float value) {
    attributes_.insert( std::pair<std::string, float>(key, value) );
}

} /* namespace curve */
} /* namespace generator_app */
