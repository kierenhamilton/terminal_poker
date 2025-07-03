#include "poker.h"


int main() {


  Game game;

  game.add_player("kieren", 10000, true);
  game.add_player("the destroyer", 100, false);
  game.setup();
  game.display_game();

  return 0;
}
