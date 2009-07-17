#pragma once
#include "io_session.h"

namespace fastnet
{

	class protocol_encoder
{
public:
	protocol_encoder(void);
	virtual ~protocol_encoder(void);

public:
	virtual any encode( io_session & session, any object ) = 0;
};

} // namespace fastnet