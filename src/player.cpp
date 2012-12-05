#include "player.hpp"

using namespace ThriftyGramophone;

int Player::play(std::string uri) {
  Device* d = registry.get_device_for_URI(uri);
  if (d == NULL) {
    return -1;
  }
  return d->play(uri);
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
