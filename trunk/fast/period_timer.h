#pragma once

namespace fastnet {
	namespace utility {
		using namespace boost;
		using namespace boost::asio;

		class period_timer : noncopyable
		{
		private:
			typedef boost::function<void( const system::error_code & err )> timer_handler;

		public:
			period_timer( io_service& ios )
				: ios_(ios)
				, timer_(ios)
				, interval_(0)
				, handler_()
			{
			}
			~period_timer(void)
			{
			}

		public:
			void start( const size_t interval, timer_handler handler )
			{
				if ( interval == 0 )
				{
					throw std::exception( "illegal interval" );
				}

				handler_ = handler;
				interval_ = interval;

				if ( interval_ != 0 )
				{
					start_timer( interval_ );
				}
			}

			void stop() {
				timer_.cancel();
			}

		private:
			void start_timer( const size_t interval )
			{
				timer_.expires_from_now( boost::posix_time::milliseconds( interval ) );
				timer_.async_wait( BOOST_BIND( &period_timer::on_timer, this, boost::asio::placeholders::error ) );
			}
			void on_timer( const system::error_code & err )
			{
				handler_( err );
				start_timer( interval_ );
			}

		private:
			io_service &		ios_;
			deadline_timer		timer_;
			size_t				interval_;
			timer_handler		handler_;
		};
	}
}