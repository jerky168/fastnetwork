#pragma once
#include "abstract_acceptor.h"
#include "io_buffer.h"
#include "types.h"
#include "datagram_session.h"

namespace fastnet
{
	namespace udp
	{
		class datagram_acceptor :
			public abstract_acceptor
		{
		public:
			datagram_acceptor(void);
			~datagram_acceptor(void);

		public:
			transport_type get_session_type() { return UDP; }

			void bind( boost::asio::ip::udp::endpoint endpoint ) {
				local_endpoint_ = endpoint;
				
				socket_.reset( new boost::asio::ip::udp::socket( ios, local_endpoint_ ) );
				// socket_->bind( local_endpoint_ );

				start_receive();
			}

			void unbind( boost::asio::ip::udp::endpoint endpoint ) {
				if( local_endpoint_ != endpoint ) {
					return ;
				}

				socket_->shutdown( ip::udp::socket::shutdown_both );
				socket_->close();
				socket_.reset();
			}

		private:
			void start_receive() {
				socket_->async_receive_from( boost::asio::buffer( buffer_ ), 
					remote_endpoint_, 
					boost::bind( &datagram_acceptor::handler_receive, 
						this, 
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred ) );
			}

			void handler_receive( const error_code & error, size_t bytes_transferred ) {
				if( !error || error == boost::asio::error::message_size ) {
					io_session_ptr session( new datagram_session( socket_, local_endpoint_, remote_endpoint_ ) );
					accept_handler->session_accepted( shared_from_this(), session );
					handle_data( bytes_transferred, remote_endpoint_ );
					start_receive();
				}
			}

			void handle_data( size_t bytes_transferred, ip::udp::endpoint remote_endpoint );

		private:
			ip::udp::endpoint			local_endpoint_;
			socket_ptr					socket_;

			ip::udp::endpoint			remote_endpoint_;
			boost::array<char, 1500>	buffer_;
		};

	} // namespace udp
} // namespace fastnet