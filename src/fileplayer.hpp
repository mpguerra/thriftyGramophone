#ifndef FILE_PLAYER_H
#define FILE_PLAYER_H

#include <string>
#include <gst/gst.h>
#include "player.hpp"

namespace ThriftyGramophone
{
    class FilePlayer : public Player
    {
        int play(std::string uri);

        Status status();

        int register_client(std::string id, Client* client);

        int unregister_client(std::string id);
    };
}
#endif
