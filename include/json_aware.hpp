#ifndef _JSONAWARE_HPP
#define _JSONAWARE_HPP

/**
 * json_aware.hpp
 * \brief JSON aware interface
 * \details Interface providing parsing object to json string
 * \author: Jan Kumor
 *  Created on: 13 Apr 2015
 *      Author: john
 */

#include <iostream>

#include <rapidjson/document.h>

namespace sledzeniekalmana {
namespace shared {

class json_aware {
public:
	virtual ~json_aware() {};

protected:
	virtual std::string to_json_string() = 0;
};

} /* namespace shared */
} /* namespace sledzeniekalmana */

#endif /* _JSONAWARE_HPP */
