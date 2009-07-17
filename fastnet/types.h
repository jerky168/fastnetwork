#pragma once

namespace fastnet
{
	namespace udp
	{
		typedef shared_ptr<ip::udp::socket> socket_ptr;
		typedef ip::udp::endpoint			endpoint;

	} // namespace udp
} // namespace fastnet