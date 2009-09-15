// client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <boost/lexical_cast.hpp>

#include "udp_session_handler.h"

io_service ios_;
session_ptr client;

void read_send( session_ptr session ) {
	string read;
	cin >> read;
	if( read == "quit" )
	{
		// session_->close();
		return ;
	}

	cout << "[SYS:send]" << read << endl;
	char send_buf[1024] = {0};
	unsigned short message_len = static_cast<unsigned short>( read.length() );
	::memcpy( send_buf, &message_len, sizeof(message_len) );
	::memcpy( send_buf + sizeof(message_len), read.c_str(), message_len );

	ios_.post(
		BOOST_BIND( 
			&io_session::write, session,
			shared_ptr<io_buffer>( new io_buffer( send_buf, message_len + sizeof(message_len)))
			)
		);
//	session->write( shared_ptr<io_buffer>( new io_buffer( send_buf, message_len + sizeof(message_len))) );
}

void session_created( session_ptr session ) {
	if( ! session ) {
		LOG( "error, not connected." );
		return ;
	}

	session_handler_ptr handler(new udp_session_handler());
	session->set_handler( handler );
	session->get_filter_chain()->session_connected( session );

	client = session;
}


void run_service( io_service & ios )
{
	boost::thread t( BOOST_BIND( &io_service::run, &ios ) );
}

int _tmain(int argc, _TCHAR* argv[])
{
	char host[20] = "127.1.1.1";
	unsigned short port = 10080;

	if( argc > 1 ) {
		::wcstombs( host, argv[1], sizeof(host) );
	}
	if( argc > 2 ) {
		try {
			port = lexical_cast<unsigned short>( wstring(argv[2]) );
		} catch( const bad_lexical_cast & ) {
			cout << "input port illegal. expected unsigned short value, but ";
			wcout << argv[2] << endl;
		}
	}


	try	{
		io_service::work work(ios_);
		run_service( ios_ );

		shared_ptr<fastnet::io_connector> connector( new udp::udp_connector( ios_ ) );
		connector->set_handler( session_created );

//		connector->connect( ip::udp::endpoint( ip::address_v4::from_string(host), port ) );
		// while using ip::address_v4::from_string(host), async_receive_from won't work
		// I don't know why.
		connector->connect( ip::udp::endpoint( ip::address_v4::from_string("127.0.0.1"), port ) );

		while ( true ) {
			if ( ! client )	{
				::Sleep(1000);
			} else {
				read_send( client );
				// break;
			}
		}
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	ios_.stop();

	while( true ) {
		::Sleep( 10000 );
	}
	
	return 0;
}
