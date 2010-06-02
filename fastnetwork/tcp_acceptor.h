#pragma once
#include "io_acceptor.h"

namespace fastnetwork {
	namespace tcp {
		using namespace std;
		using namespace boost;
		using namespace boost::asio;
		using namespace fastnetwork;

		class tcp_acceptor : public io_acceptor
		{
		public:
			tcp_acceptor( io_service & ios )
				: ios_(ios)
				, acceptor_(ios_)
				, socket_()
				, local_endpoint_(fastnetwork::TCP)
				, remote_endpoint_()
				, session_manager_()
				, create_handler_()
			{
			}
			~tcp_acceptor(void);

		public:
			void start();

			void start_accept();
			void bind( endpoint ep );
			void set_handler( function<void( shared_ptr<io_session> )> handler ) {
				create_handler_ = handler;
			}
			void stop();

		private:
			void handle_accept( const system::error_code & error ) {
				if ( error ) {
					// TODO: error
				} else {
					// TODO: create tcp session
					shared_ptr<io_session> session = session_manager_.new_session( socket_ );

						sta
				}
			}

		private:
			io_service &				ios_;
			ip::tcp::acceptor			acceptor_;
			shared_ptr<ip::tcp::socket>	socket_;		// to accept
			endpoint					local_endpoint_;
			ip::tcp::endpoint			remote_endpoint_;

			session_manager				session_manager_;

			function<void( shared_ptr<io_session> )>	create_handler_;
		};
	}
}
