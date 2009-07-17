#pragma once
#include "io_session.h"

namespace fastnet {
	class io_acceptor
	{
	public:
		io_acceptor(void){}
		virtual ~io_acceptor(void){}

	public:
		virtual void start() = 0;
		virtual void set_handler( boost::function<void( boost::shared_ptr<io_session> )> ) = 0;
	};
}
