#pragma once
#include "io_session.h"

namespace fastnetwork {
	using namespace boost;
	using namespace boost::asio;

	class io_connector
	{
	public:
		io_connector(void){}
		virtual ~io_connector(void){}

	public:
		virtual void connect( endpoint endpoint ) = 0;
		virtual void bind( endpoint endpoint ) = 0;
		virtual void set_handler( function<void( shared_ptr<io_session> )> ) = 0;
	};
}
