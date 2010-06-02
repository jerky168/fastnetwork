#pragma once

#include "types.h"

namespace fastnetwork {
class session_handler
{
public:
	virtual bool session_connected( tcp_session_ptr session, const error_code & error ) = 0;
	virtual bool session_read( tcp_session_ptr session, ::boost::asio::streambuf & data, const error_code & error, size_t bytes ) = 0;
	virtual bool session_written( tcp_session_ptr session, write_buffer_ptr msg, const error_code & error, size_t bytes ) = 0;
};

}