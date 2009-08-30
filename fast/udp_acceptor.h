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
			udp_acceptor( io_service & ios )
				: io_service_(ios)
				, socket_()
				, remote_endpoint_()
				, recv_buffer_()
			{
			}

		public:
			void bind( boost::asio::ip::udp::endpoint endpoint ) {
				socket_.reset( new ip::udp::socket(io_service_, endpoint));
			}

			void start() {
				start_receive();
			}

			void stop() {
				if ( socket_ )
				{
					socket_->close();
				}
				io_service_.stop();
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
			io_service&					io_service_;
			shared_ptr<ip::udp::socket>	socket_;
			ip::udp::endpoint			remote_endpoint_;
			array<char, 1500>			recv_buffer_;

			function<void( shared_ptr<fastnet::io_session> )>	handler_;
		};
	}
}
