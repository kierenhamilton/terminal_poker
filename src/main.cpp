#include "card_engine.h"
#include "poker1.h"
#include <iostream>
#include <iterator>

int main() {

  Game poker;

  add_player(poker, 100, "nick offerman");
  add_player(poker, 100, "dichan lachman");
  add_player(poker, 100, "brian cranston");
  add_player(poker, 100, "conan the conquorer");
  add_player(poker, 100, "john wick");


  init_game(poker);

  for (Player &p : poker.players) p.hand_shown = true;

  next_round(poker);
  next_round(poker);
  next_round(poker);

  evaluate_game(poker);

  return 0;
}
