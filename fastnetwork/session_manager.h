#pragma once
#include "endpoint.h"
#include "period_timer.h"

namespace fastnetwork {

	class io_session;

	using namespace std;
	using namespace boost;
	using namespace boost::asio;
	using namespace fastnetwork::utility;

	class session_manager : noncopyable
	{
	private:
		typedef map<endpoint, shared_ptr<io_session>>	session_map;

	public:
		session_manager( io_service & ios )
			: timer_(ios)
		{
			timer_.start( 1000, ::boost::bind( &session_manager::on_timer, this, _1 ) );
		}
		~session_manager(void){
			timer_.stop();
		}

	public:
		void on_timer( const system::error_code & err ) {
			if ( !err )
			{
				check_session_idle();
			}
		}

		shared_ptr<io_session> new_session( shared_ptr<ip::udp::socket> socket, endpoint remote );
		shared_ptr<io_session> new_session( shared_ptr<ip::tcp::socket> socket, endpoint remote );

		void close_session( shared_ptr<io_session> session );

	private:
		void check_session_idle();

		void find_idle_sessions( session_map &idle_sessions );
	private:
		mutex			mutex_;
		period_timer	timer_;
		session_map		sessions_;
	};
}