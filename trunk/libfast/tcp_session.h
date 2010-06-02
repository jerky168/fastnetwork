#pragma once
#include "types.h"

namespace fastnetwork {
	class tcp_session : public enable_shared_from_this<tcp_session> {
	public:
		// for accepted connection
		tcp_session( tcp_socket_ptr & socket )
			: so(socket)
			, read_buffer()
			, handler(NULL)
			, connected(false)
		{
		}
		// for active connection
		tcp_session(io_service & io, session_handler * h)
			: so( new ip::tcp::socket(io) )
			, read_buffer()
			, handler(h)
			, connected(false)
		{
		}
		virtual ~tcp_session() {}

	public:
		virtual void set_handler( session_handler * h ) {
			assert( h!= NULL );
			this->handler = h;
		}
		void connect( ip::tcp::endpoint & ep ) {
			so->async_connect(ep, 
				::boost::bind( &tcp_session::handle_connected, this, placeholders::error ) );
		}

		virtual void start() {
			if( handler == NULL ) {
				throw runtime_error( "no session handler." );
			}
			start_read();
		}

		virtual void close();

		virtual void write( write_buffer_ptr msg ) {
			so->get_io_service().post(
				::boost::bind( &tcp_session::do_write, this, msg ) );
		}

		ip::tcp::endpoint remote_endpoint() {
			return so->remote_endpoint();
		}
		ip::tcp::endpoint local_endpoint() {
			return so->local_endpoint();
		}

	protected:
		void start_read();

		void do_write( write_buffer_ptr &msg );

		void handle_connected( const error_code & error );

		void handle_read( const error_code & error, size_t bytes );

		void handle_written( write_buffer_ptr msg, const error_code & error, size_t bytes );

	protected:
		tcp_socket_ptr	so;
		::boost::asio::streambuf read_buffer;
		session_handler * handler;
		bool			connected;
	};

}