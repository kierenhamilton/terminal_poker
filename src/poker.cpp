#include "poker.h"
#include "card_engine.h"
#include <iostream>
#include <string>
#include <vector>

void Game::setup() {
  init_deck(deck);
  shuffle(deck);
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
    std::cout << "PREFLOP\n";
    break;
  case FLOP:
    std::cout << "FLOP\n";
    break;
  case RIVER:
    std::cout << "RIVER\n";
    break;
  case TURNOVER:
    std::cout << "TURNOVER\n";
    break;
  }
}

void Game::display_cards() {
  Card_ascii cards;
  for (Card &card : hidden_cards) {
    Card_ascii temp = get_face_down_ascii();
    cards = cards + temp;
  };

  for (Card &card : shown_cards) {
    Card_ascii temp = get_card_ascii(card);
    cards = cards + temp;
  }

  display_card_ascii(cards);
}

void Game::display_players() {
  std::string player_names = "";
  std::string username;
  for (Player player : players) {
    if (player.get_user())
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
    if (player.get_user()){
      for (Card card : player.get_player_hand()){
        temp = get_card_ascii(card);
        temp2 = temp2 + temp;
      }
      display_card_ascii(temp2);
    }
  }
}

void Game::start_round() {};

void Game::display_game() {
  this->display_phase();
  this->display_players();
  this->display_cards();
  this->display_user_hand();
}

bool Player::bet(int highest_bet) {
  int proposed_bet;
  std::cin >> proposed_bet;

  return 0;
};

