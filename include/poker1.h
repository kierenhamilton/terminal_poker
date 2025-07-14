#ifndef POKER1_H
#define POKER1_H

#include "card_engine.h"
#include <cstdint>
#include <map>
#include <string>

typedef enum { PREFLOP, FLOP, RIVER, TURNOVER, SHOWDOWN } round_t;
typedef enum { BET, CALL, FOLD } bet_t;
typedef enum {
  HIGH_CARD,
  PAIR,
  TWO_PAIR,
  THREES,
  STRAIGHT,
  FLUSH,
  FULL_HOUSE,
  FOURS,
  STRAIGHT_FLUSH,
  ROYAL_FLUSH
} ranking_t;

struct Game;

struct Eval {
  ranking_t ranking{};
  uint32_t value{};
  uint32_t secondary{};
  std::vector<uint32_t> tiebreaker{};
};

struct Player {

  std::string name{};
  std::vector<Card> hand{};
  bool is_folded{};
  uint32_t money{};
  uint32_t current_bet{};
  Card_ascii gui_cards{};
  bool is_current_turn{};
  bool hand_shown{};
  bool all_in{};
  uint32_t evaluation{};
  Eval eval{};
};

struct Card_rank {
  uint32_t rank;
  uint32_t suit;
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
  uint32_t min_bet{};
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

void display_player_cards(Game &game, std::string s);

void display_game(Game &game);

Interaction get_player_interaction();

void set_player_interaction(Player &player, Interaction &interaction,
                            uint32_t &current_bet, uint32_t &pot);

void bet(Player &player, Game &game);

void round(Game &game);

const bool is_digits(const std::string &s);

bool bets_are_equal(Game &game);

void reset_bets(Game &game);

void display_cards_ascii(std::vector<Card> &cards);

void evaluate_game(Game &game);

Eval evaluate_player(std::vector<Card> hand);

bool is_flush(Eval &eval, std::map<Suit, std::vector<Card>> &suit_frequency);
#endif
