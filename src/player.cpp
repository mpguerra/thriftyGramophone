#include "player.hpp"

using namespace ThriftyGramophone;

int Player::play(std::string URI) {
  return 0;
}

Status Player::status() {
  return this->player_status;
}

int Player::register_client(std::string id, Client* client) {
  return 0;
}

int Player::unregister_client(std::string id) {
  return 0;
}
