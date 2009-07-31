#pragma once

namespace fastnet {

	using namespace boost;
	using namespace boost::asio;

	class default_io_service : public noncopyable
	{
	public:
		default_io_service(void);
		~default_io_service(void);

	public:
		static boost::asio::io_service & get_default_service() {
			if( ! service_ ) {
				service_.reset( new boost::asio::io_service() );
				work_.reset( new boost::asio::io_service::work( *service_.get() ) );
			}
			return *(service_.get());
		}

	private:
		static shared_ptr<boost::asio::io_service>	service_;
		static shared_ptr<boost::asio::io_service::work> work_;
	};
}