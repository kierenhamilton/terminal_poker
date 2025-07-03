#include "poker.h"


int main() {


  Game game;

  game.add_player("kieren", 10000, true);
  game.add_player("player2", 10000, false);
  game.set_blind(100);
  game.setup();
  game.start_round();
  game.start_round();
  game.start_round();
  game.start_round();

  return 0;
}
