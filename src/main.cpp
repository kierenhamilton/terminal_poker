#include "card_engine.h"
#include <iostream>
#include <vector>

enum phase_e{
  PREFLOP,
  FLOP,
  RIVER,
  TURNOVER,
};


class Player {
public: 

private:

  int money;
  std::vector<Card> hand;

  bool is_big_blind;
  bool is_small_blind;

};

class Player_ai : public Player {

};

class game {
public: 
private:
  int player_number;
  phase_e phase;
  int pot;
  int active_player;
  std::vector<Player> players;
  std::vector<Card> hidden_cards;
  std::vector<Card> shown_cards;
};

int main() {

  std::vector<Card> deck;
  init_deck(deck);

  return 0;
}
