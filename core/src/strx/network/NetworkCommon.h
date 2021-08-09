#pragma once

#include <boost/asio/ip/tcp.hpp>
#include <nya.hpp>


namespace strx
{
namespace asio = boost::asio;
using boost::asio::ip::tcp;

using ConnectionId = int;

constexpr int recommendedMessageLimit = 1e7;  // about 10Mb
}  // namespace strx
