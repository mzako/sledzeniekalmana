/**
 * \file connection_commons.hpp
 * \author Adam Mościcki
 */

#ifndef _CONNECTION_COMMONS_HPP
#define _CONNECTION_COMMONS_HPP

#include <boost/thread/mutex.hpp>
#include <queue>
#include <string>

/**
 * \details Same setting for client and server
 */

namespace network {

struct connection_commons {
	static const std::string END_OF_MESSAGE;
};

}
#endif
