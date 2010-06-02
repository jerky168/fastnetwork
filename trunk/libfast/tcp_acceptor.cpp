#include "StdAfx.h"
#include "tcp_acceptor.h"
#include "accept_handler.h"

void fastnetwork::tcp_acceptor::bind( ip::tcp::endpoint & ep )
{
	acceptor.open( ep.protocol() );
	acceptor.bind(ep);
	acceptor.listen(max_connection);
	cout << "accept ok." << endl;
	start_accept();
}

void fastnetwork::tcp_acceptor::start_accept()
{
	socket.reset( new ip::tcp::socket(service) );
	cout << "waiting for connection..." << endl;
	acceptor.async_accept( *(socket.get()),
		::boost::bind( &tcp_acceptor::handle_accept, this, placeholders::error ) );
}

void fastnetwork::tcp_acceptor::handle_accept( const error_code & error )
{
	handler.handle_accept(socket, error);
	socket.reset();
	start_accept();
}