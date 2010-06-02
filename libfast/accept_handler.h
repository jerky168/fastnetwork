#pragma once
#include "types.h"

namespace fastnetwork {

	class accept_handler
	{
	public:
		virtual void handle_accept( tcp_socket_ptr so, const error_code & error ) = 0;
	};
}
