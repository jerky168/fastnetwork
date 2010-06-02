// tcp_client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

io_service service;
io_service::work work(service);

class echo_client_handler : public session_handler {
public:
	virtual bool session_connected( tcp_session_ptr session, const error_code & error ) {
		if( error ) {
			cerr << "connect error: " << error << endl;
			return false;
		}

		session->start();
		return true;
	}
	virtual bool session_read( tcp_session_ptr session, ::boost::asio::streambuf & data, const error_code & error, size_t bytes ) {
		if( error ) {
			cerr << "read error: " << error << endl;
			return false;
		}

		if( bytes > 0 ) {
			string msg( buffer_cast<const char*>( data.data() ), bytes );
			data.consume(bytes);
			cout << "<<message: " << msg << endl;
		}
		return true;
	}
	virtual bool session_written( tcp_session_ptr session, write_buffer_ptr msg, const error_code & error, size_t bytes ) {
		if( error ) {
			cerr << "send error: " << error << endl;
			return false;
		}
		cout << "sent " << bytes << " bytes." << endl;
		return true;
	}
};

void start_read_console( tcp_session_ptr client ) {
	while( true )
	{
		write_buffer_ptr msg( new string() );
		string & read = *(msg.get());
		cin >> read;
		if( read == "quit" )
		{
			client->close();
			break;
		}

		client->write(msg);
	}
}


void run_client() {
	boost::thread t( BOOST_BIND( &io_service::run, &service ) );
	ip::tcp::endpoint ep = ip::tcp::endpoint( ip::address::from_string("127.1.1.1"), 10080 );

	echo_client_handler echo;
	tcp_session_ptr client( new tcp_session(service, &echo) );
	client->connect(ep);

	start_read_console(client);

	service.stop();
	t.join();
}

int _tmain(int argc, _TCHAR* argv[])
{
	run_client();

	return 0;
}

