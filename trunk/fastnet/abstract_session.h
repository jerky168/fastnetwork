#pragma once
#include "io_session.h"

namespace fastnet
{

	class abstract_session : public io_session
	{
	public:
		abstract_session( udp::socket_ptr socket, udp::endpoint local, udp::endpoint remote );
		virtual ~abstract_session(void);

		virtual void set_handler( session_handler * handler ) {
			this->handler = handler;
		}

		virtual session_handler * get_handler() {
			return handler;
		}

		udp::endpoint get_remote_address() const {
			return remote_endpoint;
		}
		udp::endpoint get_local_address() const {
			return local_endpoint;
		}

	protected:
		udp::socket_ptr		socket;

		session_handler *	handler;

		udp::endpoint		local_endpoint;
		udp::endpoint		remote_endpoint;
	};

}