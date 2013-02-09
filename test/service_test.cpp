#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <netinet/in.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "gtest/gtest.h"
#include "../src/service.hpp"


class NullPlayer : public ThriftyGramophone::Player
{
public:
  int play(std::string URI)
  {
    return 0;
  }
};

class ThriftyGramophoneServiceTest : public ::testing::Test
{
public:
  NullPlayer m_player;
  ThriftyGramophoneServiceTest():m_thread(NULL), m_service(new ThriftyGramophone::ThriftyGramophoneService(m_player)){};
protected:
  // Start service in new thread
  virtual void SetUp()
  {
    assert(!m_thread);
    m_thread = new boost::thread(boost::bind(&ThriftyGramophoneServiceTest::startService, this));

    // m_service->
  }

  // clean
  virtual void TearDown()
  {
      // unlock
    if(m_thread != NULL)
    {
      m_service->stop();
      m_thread->join();
      delete m_thread;
      m_thread = NULL;
    }
  }

private:
  // Service thread
  boost::thread* m_thread;
  ThriftyGramophone::ThriftyGramophoneService* m_service;
  // Start service in a separate thread
  void startService()
  {
    m_service->start();
  }
};
  
TEST_F(ThriftyGramophoneServiceTest, CallingPlayOnServiceCallsPlayOnThePlayer)
{
  // wait for service to be started
  sleep(5);
  boost::shared_ptr<apache::thrift::transport::TTransport> socket(new apache::thrift::transport::TSocket("localhost", 9090));
  boost::shared_ptr<apache::thrift::transport::TTransport> transport(new apache::thrift::transport::TBufferedTransport(socket));
  boost::shared_ptr<apache::thrift::protocol::TProtocol> protocol(new apache::thrift::protocol::TBinaryProtocol(transport));
  ThriftyGramophone::ThriftyGramophoneClient client(protocol);

  socket->open();
  client.play("file:///home/pili/Test.mp3");

  socket->close();
}
