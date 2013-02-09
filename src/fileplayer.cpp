#include "fileplayer.hpp"

using namespace ThriftyGramophone;

int FilePlayer::play(std::string uri) {
  Device* d = registry.get_device_for_URI(uri);
  if (d == NULL) {
    return -1;
  }
  return d->play(uri);
}

Status FilePlayer::status() {
  return this->player_status;
}

int FilePlayer::register_client(std::string id, Client* client) {
  return 0;
}

int FilePlayer::unregister_client(std::string id) {
  return 0;
}
