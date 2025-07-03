#ifndef POKER_H
#define POKER_H

#include "card_engine.h"
#include <string>
#include <vector>
#include <iostream>

enum phase_e {
  PREFLOP,
  FLOP,
  RIVER,
  TURNOVER,
};

class Player {
public:
  Player(std::string player_name, int player_money, bool player_is_user)
      : name(player_name), money(player_money), hand(), current_bet(0),
        is_big_blind(false), is_small_blind(false), is_folded(false),
        is_user(player_is_user), current_turn(false) {}

  void bet(int &highest_bet);
  void display_player_hand();
  bool get_current_turn() { return current_turn; };
  void set_current_turn(bool turn) { current_turn = turn; std::cout << "test"; };
  void set_player_hand(Card card) { hand.push_back(card); };
  std::string get_player_name() { return name; };
  int get_player_money() { return money; };
  bool get_user() { return is_user; };
  int get_current_bet() { return current_bet; };
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
  bool is_user;
  bool current_turn;
};

class Player_ai : public Player {};

class Game {
public:
  Game()
      : player_number(0), phase(PREFLOP), pot(0), blind(100), current_bet(0),
        active_player(0), deck(), players(), hidden_cards(), shown_cards() {}
  void add_player(std::string name, int money, bool user);
  void setup();
  void display_game();
  void display_phase();
  void display_pot();
  void start_round();
  void display_cards();
  void display_players();
  void display_user_hand();
  void display_current_bets();
  void set_blind(int game_blind) { blind = game_blind; };

private:
  int player_number;
  phase_e phase;
  int pot;
  int blind;
  int current_bet;
  int active_player;
  std::vector<Card> deck;
  std::vector<Player> players;
  std::vector<Card> hidden_cards;
  std::vector<Card> shown_cards;
};

#endif
