#include "service.hpp"

using namespace ThriftyGramophone;
//using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

ThriftyGramophoneHandler::ThriftyGramophoneHandler(Player& player) : m_player(player){}

int ThriftyGramophoneHandler::play(const std::string& URI)
{
  m_player.play(URI);
}

void ThriftyGramophoneService::start(Player& player)
{
  boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
  boost::shared_ptr<ThriftyGramophoneHandler> handler(new ThriftyGramophoneHandler(player));
  boost::shared_ptr<TProcessor> processor(new ThriftyGramophoneProcessor(handler));
  boost::shared_ptr<TServerTransport> serverTransport(new TServerSocket(9090));
  boost::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());

  TSimpleServer server(processor,
                       serverTransport,
                       transportFactory,
                       protocolFactory);

  printf("Starting the thriftyGramophone daemon...\n");
  server.serve();
}

void ThriftyGramophoneService::stop()
{
  
}