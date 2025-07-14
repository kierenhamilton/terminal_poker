#include "card_engine.h"
#include "poker1.h"
#include <iostream>
#include <iterator>
#include <vector>

void get_card_ascii_vec(std::vector<Card> &hand) {
  Card_ascii card_ascii;
  for (Card &card : hand) {
    Card_ascii temp = get_card_ascii(card);
    card_ascii = card_ascii + temp;
  }
  display_card_ascii(card_ascii, "");
}

int main() {

  // Game poker;
  //
  // add_player(poker, 100, "nick offerman");
  // add_player(poker, 100, "dichan lachman");
  // add_player(poker, 100, "brian cranston");
  // add_player(poker, 100, "conan the conquorer");
  // add_player(poker, 100, "john wick");
  //
  //
  // init_game(poker);
  //
  // for (Player &p : poker.players) p.hand_shown = true;
  //
  // next_round(poker);
  // next_round(poker);
  // next_round(poker);
  //
  // evaluate_game(poker);

  std::vector<Card> deck;
  std::vector<Card> hand;

  init_deck(deck);
  shuffle(deck);
  for (int j{0}; j < 7; j++) {
    hand.clear();
    for (int i{0}; i < 7; i++)
      hand.push_back(draw_card(deck));
    evaluate_player(hand);
  }

  return 0;
}
