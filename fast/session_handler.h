#pragma once
#include "io_session.h"

namespace fastnet {
	class io_session;

	class session_handler : public boost::enable_shared_from_this<session_handler>
	{
	public:
		session_handler(void) {}
		virtual ~session_handler(void) {}

	public:
		virtual void message_received( boost::shared_ptr<io_session> session, boost::any message ) = 0;

		virtual void message_sent( boost::shared_ptr<io_session> session, boost::any message ) = 0;

		virtual void session_connected( boost::shared_ptr<io_session> session ) = 0;

		virtual void session_closed( boost::shared_ptr<io_session> session ) = 0;

		virtual void session_timeout( boost::shared_ptr<io_session> session ) = 0;
	};
}
