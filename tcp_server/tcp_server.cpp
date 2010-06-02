// tcp_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class echo_handler : public session_handler {
public:
	virtual void session_created( tcp_session_ptr session ) {

	}
	virtual bool session_read( tcp_session_ptr session, ::boost::asio::streambuf & data, const error_code & error, size_t bytes ) {
		if( error ) {
			cerr << "read error: " << error << endl;
			cout << "closing socket @ " << session->remote_endpoint() << endl;
			session->close();
			return false;
		}

		cout << "read " << bytes << " bytes." << endl;
		if( bytes == 0 ) {
			return true;
		}
//		data.commit(bytes);
		echo( data, bytes, session);
		return true;
	}
	virtual bool session_written( tcp_session_ptr session, write_buffer_ptr msg, const error_code & error, size_t bytes ) {
		if( error ) {
			cerr << "write error: " << error << endl;
			return false;
		}

		if( bytes != msg->size() ) {
			cerr << "write error. date not written complete. total bytes: " << msg->size() << ", but written: " << bytes << endl;
		}
		cout << "write: " << bytes << " bytes." << endl;
		return true;
	}

protected:
	void echo( ::boost::asio::streambuf & data, size_t bytes, tcp_session_ptr session ) {
		write_buffer_ptr msg( new string( buffer_cast<const char*>(data.data()), bytes ) );
		data.consume(bytes);
		cout << "<<message: " << *(msg.get()) << endl;
		cout << "echo..." << endl;
		session->write( msg );
	}
};


void run_server2() {
	io_service ios_;
	io_service::work work_(ios_);
	boost::thread t( BOOST_BIND( &io_service::run, &ios_ ) );

	echo_handler echo;
	tcp_session_acceptor acceptor(ios_, echo);

	ip::tcp::endpoint ep = ip::tcp::endpoint( ip::address::from_string("127.1.1.1"), 10080 );
	acceptor.bind(ep);

	cin.get();
	ios_.stop();

	t.join();
}
int _tmain(int argc, _TCHAR* argv[])
{
	run_server2();

	return 0;
}

