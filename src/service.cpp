#include "service.hpp"

using namespace ThriftyGramophone;

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

ThriftyGramophoneHandler::ThriftyGramophoneHandler(Player& player) : m_player(player){}

int ThriftyGramophoneHandler::play(const std::string& URI)
{
  m_player.play(URI);
}

ThriftyGramophoneService::ThriftyGramophoneService(Player& player) :
  m_protocolFactory(new TBinaryProtocolFactory()),
  m_handler(new ThriftyGramophoneHandler(player)),
  m_processor(new ThriftyGramophoneProcessor(m_handler)),
  m_serverTransport(new TServerSocket(9090)),
  m_transportFactory(new TBufferedTransportFactory()),
  m_server(new TSimpleServer(m_processor, m_serverTransport, m_transportFactory, m_protocolFactory)){}


void ThriftyGramophoneService::start()
{
  printf("Starting the thriftyGramophone daemon...\n");
  m_server->serve();
}

void ThriftyGramophoneService::stop()
{
  assert(m_server);
  m_server->stop();
}
