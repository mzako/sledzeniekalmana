/*
 * curve_proto.cpp
 *
 *  Created on: Jun 3, 2015
 *      Author: elohhim
 */

#include "curve_proto.hpp"

namespace generator_app {

curve_proto::~curve_proto() {
    //Do nothing
}

float curve_proto::find_attribute(std::string key) {
    std::map<std::string, float>::const_iterator it = attributes_.find(key);
    if( it == attributes_.end() )
    {
        throw(std::exception());
    } else {
        return it->second;
    }
}

void curve_proto::insert_attribute(std::string key, float value) {
    attributes_.insert( std::pair<std::string, float>(key, value) );
}

} /* namespace generator_app */
