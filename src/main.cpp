#include "card_engine.h"
#include "poker1.h"
#include <iostream>
#include <iterator>
#include <vector>

int main() {

  Game poker;

  add_player(poker, 100, "nick offerman");
  add_player(poker, 100, "dichan lachman");
  add_player(poker, 100, "brian cranston");
  add_player(poker, 100, "conan the conquorer");
  add_player(poker, 100, "john wick");

  init_game(poker);

  poker.players[0].hand_shown = true;

  round(poker);
  next_round(poker);
  round(poker);
  next_round(poker);
  round(poker);
  next_round(poker);
  round(poker);

  evaluate_game(poker);

  return 0;
}
