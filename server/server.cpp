// server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "udp_acceptor.h"

#include <boost/lexical_cast.hpp>

void parse_host( wchar_t * param, string & host ) {
	size_t size = wcstombs( NULL, param, 0 );
	size_t buffer_size = size + 1;
	scoped_array<char> buffer( new char[buffer_size] );
	size = wcstombs( buffer.get(), param, buffer_size );
	host.assign( buffer.get(), size );
}

void parse_port( wchar_t * param, unsigned short & port ) {
	try {
		port = lexical_cast<unsigned short>( wstring(param) );
	} catch( const bad_lexical_cast & e ) {
		cout << "input port illegal. expected unsigned short value, but ";
		wcout << param << endl;
	}
}

void session_accepted( session_ptr session ) {
	session_handler_ptr handler(new udp_session_handler());
	session->set_handler( handler );
}

int _tmain(int argc, _TCHAR* argv[])
{
	string host("0.0.0.0");
	unsigned short port = 10080;

	if( argc > 1 ) {
		parse_host( argv[1], host );
	}
	if( argc > 2 ) {
		parse_port( argv[2], port );
	}

	try
	{
		shared_ptr<fastnet::io_acceptor> server = fastnet::acceptor_factory::new_acceptor( fastnet::session_type::UDP );
		server->set_handler( session_accepted );
		server->start();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	cin.get();

	return 0;
}

