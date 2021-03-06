#pragma once
#include "types.h"

class udp_session_handler : public fastnetwork::session_handler
{
public:
	udp_session_handler(void);
	~udp_session_handler(void);

public:
	void message_received( session_ptr session, any message );

	void message_sent( session_ptr session, any message );

	void session_connected( session_ptr session );

	void session_closed( session_ptr session );

	void session_idle( session_ptr session ) {
		session->close();
	}
};
