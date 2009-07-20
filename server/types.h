#pragma once
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>

typedef boost::shared_ptr<fastnet::io_session> session_ptr;

typedef boost::shared_ptr<fastnet::session_handler> session_handler_ptr;

typedef boost::shared_ptr<boost::asio::ip::udp::socket> socket_ptr;

typedef boost::shared_ptr<std::string>	message_ptr;
