#include "StdAfx.h"
#include "tcp_acceptor.h"
using namespace fastnetwork::tcp;
using namespace boost;
using namespace boost::asio;

tcp_acceptor::~tcp_acceptor(void)
{
}

void fastnetwork::tcp::tcp_acceptor::bind( endpoint ep )
{
	local_endpoint_ = ep;
	acceptor_.open( ip::tcp::v4() );
	acceptor_.bind( ip::tcp::endpoint( local_endpoint_.address(), local_endpoint_.port() ) );
	acceptor_.listen();
}

void fastnetwork::tcp::tcp_acceptor::start()
{
	socket_.reset( new ip::tcp::socket(ios_) );
	acceptor_.async_accept( *socket_.get(), 
		::boost::bind( &tcp_acceptor::handle_accept, this, placeholders::error )
		);
}