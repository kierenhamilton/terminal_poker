#include "poker1.h"

int main() {


  Game poker;

  add_player(poker, 100, "nick offerman");
  add_player(poker, 100, "dichan lachman");
  add_player(poker, 100, "brian cranston");
  add_player(poker, 100, "conan the conquorer");
  add_player(poker, 100, "john wick");

  init_game(poker);

  poker.players[1].is_folded = 1;
  poker.players[3].is_current_turn = 1;
  poker.players[0].hand_shown = 1;
  poker.players[2].hand_shown = 1;

  display_interface(poker);
  display_communal_cards(poker);
  display_player_cards(poker);
  next_round(poker);
  display_interface(poker);
  display_communal_cards(poker);
  display_player_cards(poker);

  return 0;
}
