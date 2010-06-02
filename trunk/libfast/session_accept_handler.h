#pragma once
#include "accept_handler.h"

namespace fastnetwork {

class session_accept_handler : public accept_handler {
public:
	session_accept_handler( session_handler & h )
		: handler(h)
	{

	}

	virtual void handle_accept( tcp_socket_ptr so, const error_code & error );

	void close_session( tcp_session_ptr session ) {
		if( sessions.find( session ) == sessions.end() ) {
			return ;
		}
		sessions.erase( session );
	}
protected:
	tcp_session_ptr new_session( tcp_socket_ptr so );

protected:
	set<tcp_session_ptr> sessions;
	session_handler & handler;
};
}