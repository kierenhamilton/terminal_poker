#include "poker1.h"

int main() {

  Game poker;

  add_player(poker, 100, "nick offerman");
  add_player(poker, 100, "dichan lachman");
  add_player(poker, 100, "brian cranston");
  add_player(poker, 100, "conan the conquorer");
  add_player(poker, 100, "john wick");

  init_game(poker);

  evaluate_game(poker);

  return 0;
}
