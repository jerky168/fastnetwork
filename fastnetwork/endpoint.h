#pragma once

#include "transport_type.h"

namespace fastnetwork {
	using namespace boost::asio;

	class endpoint
	{

	public:
		endpoint(transport_type transport)
			: transport_(transport)
		{
		}
		endpoint( const ip::udp::endpoint & ue )
			: transport_( UDP )
			, address_( ue.address() )
			, port_( ue.port() )
		{
		}
		endpoint( const ip::tcp::endpoint & te )
			: transport_( TCP )
			, address_( te.address() )
			, port_( te.port() )
		{
		}
		~endpoint(void){}

	public:
		::boost::asio::ip::address address() const {
			return address_;
		}

		void address( const ::boost::asio::ip::address & address ) {
			address_ = address;
		}

		unsigned short port() const {
			return port_;
		}

		void port( unsigned short port ) {
			port_ = port;
		}

		transport_type transport() const {
			return transport_;
		}

	public:
		friend bool operator==( const endpoint & e1, const endpoint & e2 ) {
			if ( e1.transport_ != e2.transport_ )
			{
				return false;
			}
			if ( e1.address_ != e2.address_ )
			{
				return false;
			}
			if ( e1.port_ != e2.port_ )
			{
				return false;
			}
			return true;
		}
		friend bool operator!=( const endpoint & e1, const endpoint & e2 ) {
			if ( e1 == e2 )
			{
				return false;
			}
			return true;
		}
		friend bool operator<( const endpoint & e1, const endpoint & e2 ) {
			if ( e1.transport_ < e2.transport_ ) {
				return true;
			} else if ( e1.transport_ != e2.transport_ )	{
				return false;
			}

			if ( e1.address_ < e2.address_ ) {
				return true;
			} else if ( e1.address_ != e2.address_ )	{
				return false;
			}

			return e1.port_ < e2.port_;
		}

	private:
		transport_type				transport_;
		::boost::asio::ip::address	address_;
		unsigned short				port_;
	};

	template <typename Elem, typename Traits>
	std::basic_ostream<Elem, Traits>& operator<<(
		std::basic_ostream<Elem, Traits>& os,
		const endpoint & e)
	{
		const ::boost::asio::ip::address& addr = e.address();
		boost::system::error_code ec;
		std::string a = addr.to_string(ec);
		if (ec)
		{
			if (os.exceptions() & std::ios::failbit)
				boost::asio::detail::throw_error(ec);
			else
				os.setstate(std::ios_base::failbit);
		}
		else
		{
			if (addr.is_v4()) {
				os << a;
			} else {
				os << '[' << a << ']';
			}
			os << ':' << e.port() << '/' << e.transport();
		}
		return os;
	}
}
