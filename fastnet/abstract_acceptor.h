#pragma once
#include "session_acceptor.h"

namespace fastnet
{

	class abstract_acceptor :
		public fastnet::session_acceptor
	{
	public:
		abstract_acceptor(void);
		virtual ~abstract_acceptor(void);

	public:
		virtual void start() {
			ios.run();
		}
		virtual void stop() {
			ios.stop();
		}

		virtual void set_accept_handler( session_accept_handler * handler ) {
			this->accept_handler = handler;
		}

	protected:
		boost::asio::io_service		ios;
		session_accept_handler *	accept_handler;
	};

} // namespace fastnet