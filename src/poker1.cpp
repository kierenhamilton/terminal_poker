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

Interaction get_player_interaction(Player &player, Game &game) {
  Interaction interaction{};
  std::string user_input{};
  while (true) {
    std::cout << "f (fold), c (call), b<number> bet: ";
    std::cin >> user_input;
    if (user_input[0] == 'f') {
      interaction.type = FOLD;
      break;
    }
    if (user_input[0] == 'c') {
      interaction.type = CALL;
      break;
    }
    if (user_input[0] == 'b') {
      interaction.type = BET;
      user_input.erase(1);
      if (!user_input.empty() &&
          std::all_of(user_input.begin(), user_input.end(), ::isdigit))
        interaction.bet_amount = std::stoi(user_input);
      break;
    }
  }
  return interaction;
}
