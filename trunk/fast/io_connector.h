#pragma once
#include "io_session.h"

namespace fastnet {
	using namespace boost;
	using namespace boost::asio;

	class io_connector
	{
	public:
		io_connector(void){}
		virtual ~io_connector(void){}

	public:
		virtual void connect( ip::udp::endpoint endpoint ) = 0;
		virtual void bind( ip::udp::endpoint endpoint ) = 0;
		virtual void set_handler( function<void( shared_ptr<io_session> )> ) = 0;
	};
}
