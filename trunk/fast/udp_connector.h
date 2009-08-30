#pragma once
#include "io_connector.h"

namespace fastnet {
	namespace udp {
		class udp_connector :
			public io_connector
		{
		public:
			udp_connector( io_service& ios )
				: io_service_(ios)
				, socket_()
				, recv_buffer_()
				, handler_()
			{
			}

		public:
			void connect( ip::udp::endpoint endpoint );
			void bind( ip::udp::endpoint endpoint ) {
				socket_.reset( new ip::udp::socket(io_service_, endpoint) );
			}

			void set_handler( function<void( shared_ptr<fastnet::io_session> )> handler ) {
				this->handler_ = handler;
			}

		private:
			void start_receive();
			void handle_receive(const boost::system::error_code& error,
				std::size_t bytes_transferred);
			void handle_connect( const boost::system::error_code& error );

		private:
			io_service&					io_service_;
			shared_ptr<ip::udp::socket>	socket_;
			array<char, 1500>			recv_buffer_;
			ip::udp::endpoint			remote_endpoint_;

			function<void( shared_ptr<fastnet::io_session> )>	handler_;
		};
	}
}
