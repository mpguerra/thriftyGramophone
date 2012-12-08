#include <stdio.h>
#include "player.hpp"
#include "service.hpp"

using namespace ThriftyGramophone;
using namespace std;

int main(int argc, char **argv)
{
  Player player;
  ThriftyGramophoneService service(player);
  
  service.start();
}