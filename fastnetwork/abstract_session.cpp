#include "StdAfx.h"
#include "abstract_session.h"
#include "default_filter_chain.h"

fastnetwork::abstract_session::abstract_session( session_manager & manager, endpoint local, endpoint remote, size_t timeout_sec )
: manager_(manager)
, local_endpoint_(local)
, remote_endpoint_(remote)
, handler_()
, filter_chain_( new default_filter_chain() )
, connected_(false)
, last_active_time_()
, idle_timeout_( seconds(timeout_sec) )
, attribute_mutex_()
, attributes_()
{
}