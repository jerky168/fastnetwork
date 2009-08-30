// cheat.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define LOG(msg) { \
	::std::cout << msg << ::std::endl;	\
	}

io_service service_;
io_service::work work_(service_);
array<char, 1500>			recv_buffer_;
ip::udp::endpoint			remote_endpoint_;
ip::udp::endpoint			server_endpoint;
shared_ptr<ip::udp::socket>	socket_;

void handle_sent( const system::error_code& error, std::size_t bytes_transferred ) {
	LOG( "SENT." );
}

void handle_receive( const system::error_code& error, std::size_t bytes_transferred )
{
	if (!error || error == boost::asio::error::message_size)
	{
		LOG( "received from socket." << bytes_transferred );

		socket_->async_receive_from(
			buffer(recv_buffer_), remote_endpoint_,
			boost::bind(handle_receive,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	}
	else 
	{
		LOG( error );
	}

}

void run_service( io_service & ios )
{
	boost::thread t( BOOST_BIND( &io_service::run, &ios ) );
}

void handle_write_complete( const system::error_code& error, size_t bytes ) {
	LOG( "sent." );
}

void write( const char * buf, size_t size ) {
	socket_->async_send_to(
		boost::asio::buffer( buf, size ), 
		server_endpoint,
		boost::bind( handle_write_complete, 
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred )
		);
}

void handle_connect(const boost::system::error_code& error)
{
	LOG( "receive at local: " << socket_->local_endpoint() );
	socket_->async_receive_from(
		buffer(recv_buffer_), remote_endpoint_,
		boost::bind(handle_receive,
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));
}
int _tmain(int argc, _TCHAR* argv[])
{
	run_service( service_ );

	// socket_->open( ip::udp::v4() );
	server_endpoint = ip::udp::endpoint( ip::address_v4::from_string("127.0.0.1"), 10080 );

	socket_.reset( new ip::udp::socket( service_ ) );

	socket_->async_connect(
		server_endpoint, 
		handle_connect
		);

	while( true ) {
		string read;
		cin >> read;
		if( read == "quit" )
		{
			// session_->close();
			break;
		}

		cout << "[SYS:send]" << read << endl;
		char send_buf[1024] = {0};
		unsigned short message_len = static_cast<unsigned short>( read.length() );
		::memcpy( send_buf, &message_len, sizeof(message_len) );
		::memcpy( send_buf + sizeof(message_len), read.c_str(), message_len );

		service_.post(
			BOOST_BIND( write, send_buf, message_len + sizeof(message_len) ) 
		);
	}

	cin.get();
	return 0;
}

