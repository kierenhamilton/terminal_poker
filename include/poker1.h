#ifndef POKER1_H
#define POKER1_H

#include "card_engine.h"
#include <cstdint>
#include <string>

typedef enum { PREFLOP, FLOP, RIVER, TURNOVER, SHOWDOWN } round_t;
typedef enum { BET, CALL, FOLD } bet_t;

struct Game;

struct Player {

  std::string name{};
  std::vector<Card> hand{};
  bool is_folded{};
  uint32_t money{};
  uint32_t current_bet{};
  Card_ascii gui_cards{};
  bool is_current_turn{};
  bool hand_shown{};
};

struct Game {

  std::vector<Player> players{};
  std::vector<Card> deck{};
  std::vector<Card> hidden_cards{};
  std::vector<Card> shown_cards{};
  round_t round{};
  uint32_t pot{};
  uint32_t player_number{};
  uint32_t longest_player_name{};
  Card_ascii gui_cards{};
  uint32_t current_bet{};
};

struct Interaction {
  bet_t type;
  uint32_t bet_amount;
};

void add_player(Game &game, uint32_t money, std::string name);

void init_game(Game &game);

void next_round(Game &game);

std::string get_round(round_t &round);

void display_interface(Game &game);

void display_communal_cards(Game &game);

void display_player_cards(Game &game);

Interaction get_player_interaction(Player &player, Game &game);

#endif
