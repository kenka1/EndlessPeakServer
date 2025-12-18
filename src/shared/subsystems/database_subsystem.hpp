#pragma once

#include "utils/ts_queue.hpp"
#include "protocol/base_packet.hpp"

namespace ep
{
  class DBSubsystem {
  public:
    DBSubsystem() = default;
    ~DBSubsystem() = default;
    DBSubsystem(const DBSubsystem&) = delete;
    DBSubsystem& operator=(const DBSubsystem&) = delete;

    TSQueue<NetPacket> in_queue_;
    TSQueue<NetPacket> out_queue_;
  };
}
