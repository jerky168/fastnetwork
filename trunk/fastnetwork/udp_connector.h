#pragma once
#include "io_connector.h"
#include "udp_session_manager.h"

namespace fastnetwork {
	namespace udp {
		class udp_connector :
			public io_connector, noncopyable
		{
		public:
			udp_connector( io_service& ios )
				: io_service_(ios)
				, socket_()
				, recv_buffer_()
				, local_endpoint_(UDP)
				, manager_(io_service_)
				, create_handler_()
			{
			}

		public:
			void connect( endpoint endpoint );
			void bind( endpoint endpoint ) {
				if ( endpoint.transport() != fastnetwork::UDP )
				{
					throw std::exception("endpoint should be udp.");
				}
				ip::udp::endpoint e( endpoint.address(), endpoint.port() );
				socket_.reset( new ip::udp::socket(io_service_, e) );
			}

			void set_handler( function<void( shared_ptr<fastnetwork::io_session> )> handler ) {
				this->create_handler_ = handler;
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
			endpoint					local_endpoint_;
			ip::udp::endpoint			remote_socket_endpoint_;
			udp_session_manager			manager_;

			function<void( shared_ptr<fastnetwork::io_session> )>	create_handler_;
		};
	}
}
