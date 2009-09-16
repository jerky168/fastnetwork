// echo_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "echo_handler.h"


void show_usage( _TCHAR* app_name )
{
	cout << app_name << " ip port" << endl;
}

class accept_handler : public fastnetwork::session_accept_handler {
public:
	accept_handler( session_handler * handler ) : handler_(handler) {}

	void session_accepted( session_acceptor & acceptor, io_session & session ) {
		session.set_handler( handler_ );
	}

private:
	session_handler *	handler_;
};

int _tmain(int argc, _TCHAR* argv[])
{
	if( argc < 3 ) {
		show_usage( argv[0] );
		return 0;
	}

	string host( argv[1] );
	unsigned short port = static_cast<unsigned short>( atoi( argv[2] ) );

	session_acceptor * acceptor = session_acceptor_factory::new_session_acceptor( UDP ); // new datagram_acceptor();
	acceptor->set_handler( new accept_handler( new echo_handler() ) );
	acceptor->bind( boost::asio::ip::udp::endpoint( address::from_string( host ), port ) );
	acceptor->start();

	return 0;
}

