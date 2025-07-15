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
  Eval eval{};
  uint32_t runs{};

  uint32_t num_high_card{};
  uint32_t num_pairs{};
  uint32_t num_two_pairs{};
  uint32_t num_threes{};
  uint32_t num_straight{};
  uint32_t num_flush{};
  uint32_t num_full_house{};
  uint32_t num_fours{};
  uint32_t num_straight_flush{};
  uint32_t num_royal_flush{};

  init_deck(deck);
  // shuffle(deck);
  for (int j{0}; j < 7; j++) {
    hand.clear();
    for (int i{0}; i < 7; i++)
      hand.push_back(draw_card(deck));
    eval = evaluate_player(hand);
    switch (eval.ranking) {
    case HIGH_CARD:
      num_high_card++;
      break;
    case PAIR:
      num_pairs++;
      break;
    case TWO_PAIR:
      num_two_pairs++;
      break;
    case THREES:
      num_threes++;
      break;
    case STRAIGHT:
      num_straight++;
      break;
    case FLUSH:
      num_flush++;
      break;
    case FULL_HOUSE:
      num_full_house++;
      break;
    case FOURS:
      num_fours++;
      break;
    case STRAIGHT_FLUSH:
      num_straight_flush++;
      break;
    case ROYAL_FLUSH:
      num_royal_flush++;
      break;
    }
    runs++;
    std::cout << "num_high_card: " << num_high_card << "\n";
    std::cout << "num_pairs: " << num_pairs << "\n";
    std::cout << "num_two_pairs: " << num_two_pairs << "\n";
    std::cout << "num_threes: " << num_threes << "\n";
    std::cout << "num_straight: " << num_straight << "\n";
    std::cout << "num_flush: " << num_flush << "\n";
    std::cout << "num_full_house: " << num_full_house << "\n";
    std::cout << "num_fours: " << num_fours << "\n";
    std::cout << "num_straight_flush: " << num_straight_flush << "\n";
    std::cout << "num_royal_flush: " << num_royal_flush << "\n";
    std::cout << "HANDS: " << runs << "\n";
  }

  return 0;
}
