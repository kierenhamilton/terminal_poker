#include "poker1.h"
#include "card_engine.h"
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

void init_game(Game &game) {
  std::vector<Card> deck;
  init_deck(deck);
  shuffle(deck);

  game.pot = 0;
  game.player_number = 0;
  game.round = PREFLOP;
  uint32_t longest_name{11};

  for (Player &player : game.players) {
    player.hand.push_back(draw_card(deck));
    player.hand.push_back(draw_card(deck));

    game.player_number++;

    if (player.name.length() > longest_name)
      longest_name = player.name.length();

    Card_ascii player_cards{};
    for (Card &card : player.hand) {
      Card_ascii temp{get_card_ascii(card)};
      player_cards = player_cards + temp;
    }
    player.gui_cards = player_cards;
  }

  game.longest_player_name = longest_name;

  for (int i = 0; i < 5; i++) {
    Card_ascii temp{get_face_down_ascii()};
    game.gui_cards = game.gui_cards + temp;
    game.hidden_cards.push_back(draw_card(deck));
  }

  game.deck = deck;
}

void next_round(Game &game) {
  switch (game.round) {
  case PREFLOP:
    for (int i{0}; i < 3; i++) {
      game.shown_cards.push_back(draw_card(game.hidden_cards));
    }
    game.round = FLOP;
    break;
  case FLOP:
    game.shown_cards.push_back(draw_card(game.hidden_cards));
    game.round = RIVER;
    break;
  case RIVER:
    game.shown_cards.push_back(draw_card(game.hidden_cards));
    game.round = TURNOVER;
    break;
  case TURNOVER:
    game.shown_cards.push_back(draw_card(game.hidden_cards));
    game.round = SHOWDOWN;
    break;
  case SHOWDOWN:
    break;
  }

  Card_ascii community_cards{};
  for (Card &card : game.shown_cards) {
    Card_ascii temp{get_card_ascii(card)};
    community_cards = community_cards + temp;
  }
  for (const Card &card : game.hidden_cards) {
    Card_ascii temp{get_face_down_ascii()};
    community_cards = community_cards + temp;
  }
  game.gui_cards = community_cards;
}

std::string get_round(round_t &round) {
  switch (round) {
  case PREFLOP:
    return "PREFLOP";
  case FLOP:
    return "FLOP";
  case RIVER:
    return "RIVER";
  case TURNOVER:
    return "TURNOVER";
  case SHOWDOWN:
    return "SHOWDOWN";
  }
  return "";
}

void add_player(Game &game, uint32_t money, std::string name) {

  Player temp;
  temp.name = name;
  temp.money = money;
  temp.current_bet = 0;
  game.players.push_back(temp);
}

void display_interface(Game &game) {

  std::string phase{get_round(game.round)};

  std::string names;
  std::string money;
  std::string round_status;

  std::cout << std::string(
                   game.player_number * (game.longest_player_name + 5) - 1, '-')
            << "\n";
  for (const Player &player : game.players) {
    uint32_t name_buffer;
    uint32_t status_buffer;
    uint32_t money_buffer;

    name_buffer = game.longest_player_name - player.name.length() + 2;
    if (player.is_current_turn) {
      names += "> ";
      name_buffer -= 2;
    }
    names += player.name;
    names += std::string(name_buffer, ' ');
    names += " | ";
    money_buffer = game.longest_player_name -
                   std::to_string(player.money).length() + 2 - 8;
    money += ("Money: £" + std::to_string(player.money));
    money += std::string(money_buffer, ' ');
    money += " | ";
    if (player.is_folded) {
      round_status += "FOLDED";
      status_buffer = game.longest_player_name -
                      std::to_string(player.current_bet).length() + 2 - 5;
    } else {
      round_status += ("bet: £" + std::to_string(player.current_bet));
      status_buffer = game.longest_player_name + 2 - 6 -
                      std::to_string(player.current_bet).length();
    }
    round_status += std::string(status_buffer, ' ');
    round_status += " | ";
  }
  std::cout << names << "\n" << money << "\n" << round_status << "\n";
  std::cout << std::string(
                   game.player_number * (game.longest_player_name + 5) - 1, '-')
            << "\n";
  std::cout << phase << ": Betting @ £" << game.current_bet << "\n";
  std::cout << "Pot @ £" << game.pot << "\n";
}

void display_communal_cards(Game &game) { display_card_ascii(game.gui_cards); }

void display_player_cards(Game &game) {
  for (Player &player : game.players) {
    if (!player.hand_shown)
      continue;
    display_card_ascii(player.gui_cards);
  }
}

Interaction get_player_interaction() {
  Interaction interaction{};
  std::string user_input{};
  while (true) {
    std::cout << "f (fold), c (call), r<number> raise: ";
    std::cin >> user_input;
    if (user_input[0] == 'f') {
      interaction.type = FOLD;
      break;
    }
    if (user_input[0] == 'c') {
      interaction.type = CALL;
      break;
    }
    if (user_input[0] == 'r') {
      user_input.erase(0, 1);
      if (is_digits(user_input)) {
        interaction.type = BET;
        interaction.bet_amount = stoi(user_input);
        break;
      }
    }
    std::cout << "invalid\n";
  }
  return interaction;
}

const bool is_digits(const std::string &s) {
  if (s.empty())
    return false;
  for (const char &c : s)
    if (!std::isdigit(c))
      return false;
  return true;
}

bool set_player_interaction(Player &player, Interaction interaction,
                            uint32_t &current_bet, uint32_t &pot) {
  switch (interaction.type) {
  case FOLD:
    player.is_folded = true;
    return true;
  case BET:
    if (player.money < interaction.bet_amount + current_bet) {
      std::cout << "bet exceeds funds\n";
      return false;
    }
    player.money -= (current_bet - player.current_bet) + interaction.bet_amount;
    pot += (current_bet - player.current_bet) + interaction.bet_amount;
    player.current_bet = current_bet += interaction.bet_amount;
    current_bet = player.current_bet;
    return true;
  case CALL:
    player.money -= current_bet - player.current_bet;
    pot += current_bet - player.current_bet;
    player.current_bet = current_bet;
    return true;
  default:
    return false;
  }
}

void display_game(Game &game) {
  system("clear");
  display_interface(game);
  display_communal_cards(game);
  display_player_cards(game);
}

void bet(Player &player, Game &game) {
  while (true)
    if (set_player_interaction(player, get_player_interaction(),
                               game.current_bet, game.pot))
      break;
}

void round(Game &game) {
  bool round = 0;
  while (true) {
    for (Player &player : game.players) {
      if (player.is_folded || player.all_in)
        continue;
      player.is_current_turn = true;
      display_game(game);
      bet(player, game);
      player.is_current_turn = false;
      if (bets_are_equal(game) && round)
        break;
    }
    if (bets_are_equal(game))
      break;
    round = 1;
  }
  reset_bets(game);
}

bool bets_are_equal(Game &game) {
  Player *player_ptr = nullptr;
  for (Player &player : game.players) {
    if (player.all_in || player.is_folded)
      continue;
    player_ptr = &player;
  }

  if (!player_ptr)
    return true;

  for (Player &player : game.players) {
    if (player.is_folded || player.all_in)
      continue;
    if (player.current_bet != player_ptr->current_bet)
      return false;
  }
  return true;
}

void reset_bets(Game &game) {
  for (Player &player : game.players)
    player.current_bet = 0;
  game.current_bet = 0;
}

void evaluate_game(Game &game) {
  std::vector<Card> communal = game.shown_cards;
  std::vector<Card> temp1 = game.hidden_cards;
  communal.insert(communal.end(), temp1.begin(), temp1.end());

  for (Player &player : game.players) {
    std::vector<Card> player_hand = player.hand;
    player_hand.insert(player_hand.end(), communal.begin(), communal.end());

    player.hand_shown = true;
  }
}

Eval evaluate_player(std::vector<Card> &hand) {
  Eval eval{};

  return eval;
}

bool is_flush(const std::vector<Card> &hand) {
  uint32_t spade_count{};
  uint32_t club_count{};
  uint32_t heart_count{};
  uint32_t diamond_count{};

  for (const Card &card : hand) {
    switch (card.suit) {
    case Suit::SPADES:
      spade_count++;
      break;
    case Suit::CLUBS:
      club_count++;
      break;
    case Suit::HEARTS:
      heart_count++;
      break;
    case Suit::DIAMONDS:
      diamond_count++;
      break;
    }
  }
  if (spade_count >= 5 || club_count >= 5 || heart_count >= 5 ||
      diamond_count >= 5)
    return true;
  else
    return false;
}

bool is_pair(const std::vector<Card> &hand) {
  for (int i = 0; i < 6; i++) {
    for (int j = i + 1; j < 7; j++) {
      if (hand[i].value == hand[j].value)
        return true;
    }
  }
  return false;
}

bool is_two_pair(const std::vector<Card> &hand) {
  uint32_t number{};
  const Value *value_ptr = nullptr;
  for (int i = 0; i < 6; i++) {
    for (int j = i + 1; j < 7; j++) {
      if (hand[i].value == hand[j].value) {
        number++;
        if (!value_ptr) {
          value_ptr = &hand[i].value;
          continue;
        }
        if (hand[i].value == *value_ptr) continue;
        number++;
      }
    }
  }
  if (number == 2) return true;
  else return false;
}
