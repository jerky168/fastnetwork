#include "StdAfx.h"
#include "tcp_session.h"
#include "session_handler.h"
#include "session_accept_handler.h"

void fastnetwork::tcp_session::close()
{
	connected = false;
	so->close();
}

void fastnetwork::tcp_session::handle_read( const error_code & error, size_t bytes )
{
	if( ! handler->session_read(shared_from_this(), read_buffer, error, bytes ) ) {
		return ;
	}
	start_read();
}

void fastnetwork::tcp_session::handle_written( write_buffer_ptr msg, const error_code & error, size_t bytes )
{
	if( ! handler->session_written( shared_from_this(), msg, error, bytes ) ) {
		return ;
	}
}

void fastnetwork::tcp_session::handle_connected( const error_code & error )
{
	if ( ! handler->session_connected(shared_from_this(), error) ) {
		so->close();
		return ;
	}

	connected = true;
}

void fastnetwork::tcp_session::start_read()
{
	cout << "reading data..." << endl;
	async_read( *(so.get()), read_buffer,
		boost::asio::transfer_at_least(1),
		::boost::bind( &tcp_session::handle_read, this, 
		placeholders::error, placeholders::bytes_transferred ) );
}

void fastnetwork::tcp_session::do_write( write_buffer_ptr &msg )
{
	async_write( *(so.get()), buffer( *(msg.get()) ),
		::boost::bind( & tcp_session::handle_written, this, 
		msg, placeholders::error, placeholders::bytes_transferred ) );
}