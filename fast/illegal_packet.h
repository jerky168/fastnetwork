#pragma once

namespace fastnet {

class illegal_packet :
	public std::exception
{
public:
	illegal_packet(void) {}
	~illegal_packet(void) {}
};

}