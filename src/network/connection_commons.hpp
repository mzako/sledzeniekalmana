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

/**
 * Structure contains common params for server and client.
 */
struct connection_commons {
    /**
     * string which marks the end of message
     */
	static const std::string END_OF_MESSAGE;
};

}
#endif
