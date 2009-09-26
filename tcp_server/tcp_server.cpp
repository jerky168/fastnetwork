// tcp_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

ip::tcp::endpoint remote_endpoint_;
boost::array<char, 1000> buf;
io_service ios_;
io_service::work work_(ios_);
ip::tcp::socket * s_;

void handle_sent( const system::error_code & error, size_t bytes ) {
	if ( error )
	{
		cout << "error: " << error << endl;
		return ;
	}

	cout << "write " << bytes << " bytes." << endl;

	s_->close();
}

void handle_read( const system::error_code & error, size_t bytes ) {
	if ( error )
	{
		if ( error.value() != boost::asio::error::eof )
		{
			cout << "error: " << error << endl;
			return ;
		}
	}

	cout << string( buf.data(), bytes ) << endl;

	async_write( *s_, buffer(buf),
		handle_sent );
		//::boost::bind( handle_sent, placeholders::error, placeholders::bytes_transferred ) );
}

void handle_accept( const system::error_code & error ) {
	if ( error )
	{
		cout << "error: " << error << endl;
		return ;
	}
	cout << "accepted client from: " << s_->remote_endpoint() << " @ " << s_->local_endpoint() << endl;
	async_read( *s_, buffer( buf ),
		handle_read );
}

int _tmain(int argc, _TCHAR* argv[])
{

	boost::thread t( BOOST_BIND( &io_service::run, &ios_ ) );

	ip::tcp::endpoint ep = ip::tcp::endpoint( ip::address::from_string("127.1.1.1"), 10080 );
	ip::tcp::acceptor a_(ios_ );
	a_.open( ip::tcp::v4() );
	a_.bind( ep );
	a_.listen(100);

	cout << "bind at: " << a_.local_endpoint() << endl;

	s_ = new ip::tcp::socket(ios_);
	a_.async_accept( *s_, handle_accept );

	cin.get();

	delete s_;
	ios_.stop();
	t.join();

	return 0;
}

