#ifndef PLAYER_H
#define PLAYER_H

#include <string>

namespace ThriftyGramophone {

  enum State {
    PLAYING,
    PAUSED,
    STOPPED,
  };

  class Status {
  private:
    State state;
    std::string URI;
    int time; // How far into the song we are        
  };

  class Client {
    virtual std::string next_song() = 0;
  };

  class Player {
  private:
    Status player_status;

  public:
    int play(std::string URI);
    Status status();

    /**
     * Player takes ownership of passed in client
     */
    int register_client(std::string id, Client* client);
    int unregister_client(std::string id);
  };
}

#endif
