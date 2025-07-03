#include "poker.h"
#include "card_engine.h"
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

void Game::setup() {
  init_deck(deck);
  shuffle(deck);
  current_bet = blind;
  for (int i = 0; i < 5; i++)
    hidden_cards.push_back(draw_card(deck));

  for (int i = 0; i < 2; i++) {

    for (Player &player : players) {
      player.set_player_hand(draw_card(deck));
    }
  }
}

void Game::add_player(std::string name, int money, bool user) {
  players.push_back(Player(name, money, user));
  player_number++;
}

void Game::display_phase() {
  switch (phase) {
  case PREFLOP:
    std::cout << "PREFLOP";
    break;
  case FLOP:
    std::cout << "FLOP";
    break;
  case RIVER:
    std::cout << "RIVER";
    break;
  case TURNOVER:
    std::cout << "TURNOVER";
    break;
  }
  std::cout << ": Betting @ £" << current_bet << "\n";
}

void Game::display_cards() {
  Card_ascii cards;

  for (Card &card : shown_cards) {
    Card_ascii temp = get_card_ascii(card);
    cards = cards + temp;
  }
  for (Card &card : hidden_cards) {
    Card_ascii temp = get_face_down_ascii();
    cards = cards + temp;
  };

  display_card_ascii(cards);
}

void Game::display_players() {
  std::string player_names = "";
  std::string username;
  for (Player player : players) {
    if (player.get_current_turn())
      username = "> " + player.get_player_name();
    else
      username = player.get_player_name();

    player_names = player_names + username + ": £" +
                   std::to_string(player.get_player_money()) + ", ";
  }
  std::cout << player_names << "\n";
}

void Game::display_user_hand() {
  Card_ascii temp;
  Card_ascii temp2;
  for (Player player : players) {
    if (player.get_user()) {
      for (Card card : player.get_player_hand()) {
        temp = get_card_ascii(card);
        temp2 = temp2 + temp;
      }
      display_card_ascii(temp2);
    }
  }
}

int Player::bet(int &highest_bet) {
  int player_bet = 0;
  std::string user_input;
  while (true) {

    player_bet = 0;
    std::cout << "Place Bet: ";

    std::cin >> user_input;

    if (user_input[0] == 'f') {
      is_folded = 1;
      break;
    }
    if (user_input[0] == 'c') {
      player_bet = highest_bet - current_bet;
      std::cout << "testing";
    }
    if (user_input[0] == 'r') {
      player_bet = std::stoi(user_input.substr(1));
    }

    if (player_bet + current_bet >= highest_bet && player_bet < money) {
      highest_bet = player_bet + current_bet;
      current_bet = player_bet + current_bet;
      money -= player_bet;
      break;
    }
  }
  return player_bet;
}

void Game::display_pot() {
  std::cout << "Pot: £" << std::to_string(pot) << "\n";
}

void Game::start_round() {
  while (true) {

    for (Player &player : players) {
      if (player.get_folded())
        continue;
      std::string test;
      player.set_current_turn(true);
      this->display_game();
      this->update_pot(player.bet(current_bet));
      player.set_current_turn(false);
      if (all_bets_equal())
        break;
    }
    if (all_bets_equal())
      break;
  }
  switch (phase) {
  case PREFLOP:
    phase = FLOP;
    break;
  case FLOP:
    phase = RIVER;
    break;
  case RIVER:
    phase = TURNOVER;
    break;
  case TURNOVER:
    phase = PREFLOP;
    break;
  }
  current_bet = minimum_bet;
  reset_player_bets();
  this->turn_cards();
};

void Game::display_game() {

  system("clear");
  this->display_phase();
  this->display_pot();
  this->display_players();
  this->display_current_bets();
  this->display_cards();
  this->display_user_hand();
}

void Game::display_current_bets() {
  for (Player player : players) {
    if (player.get_folded())
      std::cout << "FOLDED, ";
    else
      std::cout << "Bet: £" + std::to_string(player.get_current_bet()) << ", ";
  }
  std::cout << "\n";
}

void Game::turn_cards() {
  int count = 0;
  switch (phase) {
  case PREFLOP:
    break;
  case FLOP:
    count = 3;
    break;
  case RIVER:
    count = 1;
    break;
  case TURNOVER:
    count = 1;
    break;
  }

  shown_cards.insert(shown_cards.end(),
                     std::make_move_iterator(hidden_cards.begin()),
                     std::make_move_iterator(hidden_cards.begin() + count));

  hidden_cards.erase(hidden_cards.begin(), hidden_cards.begin() + count);
}

bool Game::all_bets_equal() {
  Player *ref = nullptr;
  for (Player player : players)
    if (!player.get_folded()) {
      ref = &player;
      break;
    }

  if (!ref)
    return true;

  for (Player &player : players) {

    if (player.get_folded())
      continue;
    if (player.get_current_bet() != ref->get_current_bet())
      return false;
  }
  return true;
}

void Game::reset_player_bets() {
  for (Player &player : players) {
    player.set_current_bet(0);
  }
}
