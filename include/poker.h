#ifndef POKER_H
#define POKER_H

#include "card_engine.h"
#include <iostream>
#include <string>
#include <vector>

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

  int bet(int &highest_bet);
  bool get_folded() { return is_folded; };
  void display_player_hand();
  bool get_current_turn() { return current_turn; };
  void set_current_turn(bool turn) { current_turn = turn; };
  void set_player_hand(Card card) { hand.push_back(card); };
  std::string get_player_name() { return name; };
  int get_player_money() { return money; };
  bool get_user() { return is_user; };
  int get_current_bet() { return current_bet; };
  void set_current_bet(int setting_bet) { current_bet = setting_bet; };
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
      : player_number(0), phase(PREFLOP), pot(0), blind(100), minimum_bet(50),
        current_bet(0), active_player(0), deck(), players(), hidden_cards(),
        shown_cards() {}
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
  bool all_bets_equal();
  void reset_player_bets();
  void update_pot(int pot_input) { pot += pot_input; };
  void poker();
  void turn_cards();
  Player get_winner();
  void set_blind(int game_blind) { blind = game_blind; };
  void set_min_bet(int min_bet) { minimum_bet = min_bet; };

private:
  int player_number;
  phase_e phase;
  int pot;
  int blind;
  int minimum_bet;
  int current_bet;
  int active_player;
  std::vector<Card> deck;
  std::vector<Player> players;
  std::vector<Card> hidden_cards;
  std::vector<Card> shown_cards;
};

#endif
