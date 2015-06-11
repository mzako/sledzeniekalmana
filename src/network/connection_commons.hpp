/**
 * \file connection_commons.hpp
 * \author Adam Mościcki
 */

#ifndef _CONNECTION_COMMONS_HPP
#define _CONNECTION_COMMONS_HPP

#include <boost/thread/mutex.hpp>
#include <queue>
#include <string>

namespace network {

/**
 * \brief Structure contains common parameters for server and client.
 */
struct connection_commons {
    /**
     * string which marks the end of message
     */
	static const std::string END_OF_MESSAGE;
	/**
	 * end of connections, client will stop the main thread after receiving this message
	 */
	static const std::string CLOSE_CONNECTION;
};

}
#endif
