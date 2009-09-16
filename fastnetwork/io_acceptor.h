#pragma once
#include "io_session.h"

namespace fastnetwork {
	class io_acceptor
	{
	public:
		io_acceptor(void){}
		virtual ~io_acceptor(void){}

	public:
		//************************************
		// Method:    start, start to accept client connections
		// FullName:  fastnetwork::io_acceptor::start
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void start() = 0;
		
		//************************************
		// Method:    bind, bind to specified local endpoint
		// FullName:  fastnetwork::io_acceptor::bind
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: boost::asio::ip::udp::endpoint endpoint
		//************************************
		virtual void bind( endpoint endpoint ) = 0;

		//************************************
		// Method:    set_handler, set the accept handler. accept handler could init session on created.
		// FullName:  fastnetwork::io_acceptor::set_handler
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: boost::function<void
		// Parameter: boost::shared_ptr<io_session> 
		//************************************
		virtual void set_handler( boost::function<void( boost::shared_ptr<io_session> )> ) = 0;

		//************************************
		// Method:    stop, stop acceptting new connections.
		// FullName:  fastnetwork::io_acceptor::stop
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void stop() = 0;
	};
}
