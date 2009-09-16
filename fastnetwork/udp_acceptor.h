#pragma once

#include "io_acceptor.h"
#include "udp_session.h"
#include "udp_session_manager.h"

namespace fastnetwork {
	namespace udp {
		using namespace std;
		using namespace boost;
		using namespace boost::asio;

		class udp_acceptor : public fastnetwork::io_acceptor, noncopyable
		{
		public:
			udp_acceptor( io_service & ios )
				: io_service_(ios)
				, socket_()
				, local_(UDP)
				, remote_endpoint_()
				, recv_buffer_()
				, session_manager_(io_service_)
			{
			}

		public:
			void bind( endpoint endpoint ) {
				local_ = endpoint;
				socket_.reset( new ip::udp::socket(io_service_, ip::udp::endpoint(local_.address(),local_.port())));
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

			void set_handler( boost::function<void( shared_ptr<fastnetwork::io_session> )> handler ) {
				this->create_handler_ = handler;
			}

			void close_session( shared_ptr<io_session> session ) {
				session_manager_.close_session(session);
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
			endpoint					local_;
			ip::udp::endpoint			remote_endpoint_;
			array<char, 1500>			recv_buffer_;
			udp_session_manager			session_manager_;

			function<void( shared_ptr<fastnetwork::io_session> )>	create_handler_;
		};
	}
}
