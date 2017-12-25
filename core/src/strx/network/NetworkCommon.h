#pragma once

#include <nya.hpp>
#include <boost/asio/ip/tcp.hpp>


namespace strx
{
namespace asio = boost::asio;
using NetId = llong;
using boost::asio::ip::tcp;

constexpr int recommendedMessageLimit = 1e7; // about 10Mb


inline NetId to_netid(tcp::endpoint ep) { return (*(NetId*)ep.data() << 16) ^ ep.port(); }
}
