#pragma once
#include "session_handler.h"
#include "session_filter_chain.h"

namespace fastnet {
	using namespace std;
	using namespace boost;
	using namespace boost::asio;

	class session_handler;
	class session_filter_chain;

	class io_session : public enable_shared_from_this<io_session>
	{
	public:
		io_session(void) {}
		virtual ~io_session(void){}

	public:
		virtual void set_handler( shared_ptr<session_handler> handler ) = 0;
		virtual shared_ptr<session_handler> get_handler() = 0;

		virtual shared_ptr<session_filter_chain> get_filter_chain() = 0;

		virtual ip::udp::endpoint get_remote_endpoint() const = 0;
		virtual ip::udp::endpoint get_local_endpoint() const = 0;		
		virtual void write( any object ) = 0;
		virtual void close() = 0;

		virtual void handle_write_complete(any message,
			const system::error_code& /*error*/,
			size_t /*bytes_transferred*/) = 0;

		//************************************
		// Method:    set_attribute, set an attribute value in this session. support session storage
		// FullName:  fastnet::io_session::set_attribute
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: const string & key
		// Parameter: any value
		//************************************
		virtual void set_attribute( const string & key, any value ) = 0;
		//************************************
		// Method:    get_attribute, get the attribute
		// FullName:  fastnet::io_session::get_attribute
		// Access:    virtual public 
		// Returns:   boost::any
		// Qualifier:
		// Parameter: const string & key
		//************************************
		virtual any get_attribute( const string & key ) = 0;
	};
}
