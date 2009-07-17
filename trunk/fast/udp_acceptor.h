#pragma once

#include "io_acceptor.h"
#include "udp_session.h"

namespace fastnet {
	namespace udp {
		using namespace std;
		using namespace boost;
		using namespace boost::asio;

		class udp_acceptor : public fastnet::io_acceptor
		{
		public:
			udp_acceptor()
				: io_service_()
				, local_endpoint_(ip::udp::v4(),20000)
				, socket_(new ip::udp::socket(io_service_, local_endpoint_))
				, remote_endpoint_()
				, recv_buffer_()
			{
			}
			udp_acceptor( unsigned short port )
				: io_service_()
				, local_endpoint_(ip::udp::v4(), port)
				, socket_( new ip::udp::socket(io_service_, local_endpoint_) )
				, remote_endpoint_()
				, recv_buffer_()
			{
			}

			udp_acceptor( const string & host, unsigned short port )
				: io_service_()
				, local_endpoint_(boost::asio::ip::address::from_string(host), port)
				, socket_( new ip::udp::socket(io_service_, local_endpoint_) )
				, remote_endpoint_()
				, recv_buffer_()
			{
			}

			udp_acceptor( const boost::asio::ip::address & addr, unsigned short port )
				: io_service_()
				, local_endpoint_(addr, port)
				, socket_( new ip::udp::socket(io_service_, local_endpoint_) )
				, remote_endpoint_()
				, recv_buffer_()
			{
			}

		public:
			void start() {
				start_receive();
				io_service_.run();
			}

			void set_handler( boost::function<void( shared_ptr<fastnet::io_session> )> handler ) {
				this->handler_ = handler;
			}

		private:
			void start_receive()
			{
				socket_->async_receive_from(
					boost::asio::buffer(recv_buffer_), remote_endpoint_,
					boost::bind(&udp_acceptor::handle_receive, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
			}

			void handle_receive(const boost::system::error_code& error,
				std::size_t bytes_transferred);

		private:
			boost::asio::io_service		io_service_;
			ip::udp::endpoint				local_endpoint_;
			boost::shared_ptr<boost::asio::ip::udp::socket>	socket_;
			ip::udp::endpoint				remote_endpoint_;
			boost::array<char, 1500>	recv_buffer_;

			boost::function<void( shared_ptr<fastnet::io_session> )>	handler_;
		};
	}
}
