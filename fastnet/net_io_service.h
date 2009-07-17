#pragma once

namespace fastnet
{
	class net_io_service
	{
	public:
		net_io_service() {}
		virtual ~net_io_service() {}

	public:
		virtual void start() = 0;
		virtual void stop() = 0;
	};
}