#pragma once

#include <boost/asio.hpp>
#include <cstdint>


namespace NetworkUtils {

//using TUiid = boost::uuids::uuid;

using TMessageSize = std::uint64_t;
using TMessageNumericType = std::uint8_t;
using THeaderSize = std::uint8_t;
using TTcpSocket = boost::asio::ip::tcp::socket;
using TUdpSocket = boost::asio::ip::udp::socket;


enum class MessageType : std::uint8_t
{
    BASE,
    PING,
    PONG,
    LOGIN,
    REGISTRATION,
    TEXT,
    VOICE,
    ARCHIVE,
    SCREENSHOT,
    VIDEO,
    INVALID
};

}
    