#pragma once
#include "session_handler.h"
#include "session_filter_chain.h"
#include "endpoint.h"

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
		//************************************
		// Method:    set_handler
		// FullName:  fastnet::io_session::set_handler
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: shared_ptr<session_handler> handler
		//************************************
		virtual void set_handler( shared_ptr<session_handler> handler ) = 0;
		//************************************
		// Method:    get_handler
		// FullName:  fastnet::io_session::get_handler
		// Access:    virtual public 
		// Returns:   shared_ptr<session_handler>
		// Qualifier:
		//************************************
		virtual shared_ptr<session_handler> get_handler() = 0;

		//************************************
		// Method:    get_filter_chain
		// FullName:  fastnet::io_session::get_filter_chain
		// Access:    virtual public 
		// Returns:   shared_ptr<session_filter_chain>
		// Qualifier:
		//************************************
		virtual shared_ptr<session_filter_chain> get_filter_chain() = 0;

		virtual endpoint get_remote_endpoint() const = 0;
		virtual endpoint get_local_endpoint() const = 0;		
		//************************************
		// Method:    write, write an object. filters associated will transform the object to network bytes, and then send to the other end point.
		// FullName:  fastnet::io_session::write
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: any object
		//************************************
		virtual void write( any object ) = 0;
		//************************************
		// Method:    close, close the session.
		// FullName:  fastnet::io_session::close
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void close() = 0;

		//************************************
		// Method:    handle_write_complete, 
		// FullName:  fastnet::io_session::handle_write_complete
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: any message
		// Parameter: const system::error_code &
		// Parameter: size_t
		//************************************
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

		//************************************
		// Method:    remove_attribute
		// FullName:  fastnet::io_session::remove_attribute
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: const string & key
		//************************************
		virtual void remove_attribute( const string & key ) = 0;

		//************************************
		// Method:    is_connected
		// FullName:  fastnet::io_session::is_connected
		// Access:    virtual public 
		// Returns:   bool
		// Qualifier:
		//************************************
		virtual bool is_connected() = 0;

		//************************************
		// Method:    connected
		// FullName:  fastnet::io_session::connected
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void connected() = 0;
	};
}
