#ifndef POKER_H
#define POKER_H

#include "card_engine.h"
#include <string>
#include <vector>

enum phase_e {
  PREFLOP,
  FLOP,
  RIVER,
  TURNOVER,
};

void display_face_down();

class Player {
public:
  Player(std::string player_name, int player_money)
      : name(player_name), money(player_money), hand(), current_bet(0),
        is_big_blind(false), is_small_blind(false), is_folded(false) {}

  void display_player_hand();

  void set_player_hand(Card card) { hand.push_back(card); };
  std::vector<Card> get_player_hand() { return hand; };

  virtual ~Player() = default;

private:
  std::string name;
  int money;
  std::vector<Card> hand;
  int current_bet;
  bool is_big_blind;
  bool is_small_blind;
  bool is_folded;
};

class Player_ai : public Player {};

class Game {
public:
  Game()
      : player_number(0), phase(PREFLOP), pot(0), active_player(0), deck(),
        players(), hidden_cards(), shown_cards() {}
  void add_player(std::string name, int money);
  void setup();
  void start_round();
  void display_cards();
  void display_players();

private:
  int player_number;
  phase_e phase;
  int pot;
  int active_player;
  std::vector<Card> deck;
  std::vector<Player> players;
  std::vector<Card> hidden_cards;
  std::vector<Card> shown_cards;
};

#endif
