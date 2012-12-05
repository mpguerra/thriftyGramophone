#ifndef service_hpp 
#define service_hpp
#include <netinet/in.h>
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "gen-cpp/ThriftyGramophone.h"
#include "player.hpp"
#include <string>
#include <tr1/memory>

namespace ThriftyGramophone{

  class ThriftyGramophoneHandler : public ThriftyGramophoneIf
  {

  public:
    Player& m_player;
    ThriftyGramophoneHandler(Player& player);
    int play(const std::string& URI);
  };

  class ThriftyGramophoneService
  {
  public:
    void start(Player& player);
    void stop();
  };
}

#endif