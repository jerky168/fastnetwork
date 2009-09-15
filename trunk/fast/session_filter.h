#pragma once
#include "io_session.h"

namespace fastnet {
	using namespace std;
	using namespace boost;

	class io_session;

	class session_filter
	{
	public:
		session_filter(void) {}
		virtual ~session_filter(void) {}

	public:
		virtual void session_connected( shared_ptr<io_session> session ) =0;
		virtual void session_closed( shared_ptr<io_session> session ) =0;
		virtual void session_idle( shared_ptr<io_session> session ) =0;
		virtual any filter_receive( shared_ptr<io_session> session, any packet ) =0;
		virtual any filter_send( shared_ptr<io_session> session, any packet ) =0;
	};

}