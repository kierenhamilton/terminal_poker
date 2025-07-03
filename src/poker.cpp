#include "poker.h"
#include "card_engine.h"
#include <iostream>
#include <string>
#include <string_view>
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

void Game::add_player(std::string name, int money) {
  players.push_back(Player(name, money));
  player_number++;
}

void Game::display_cards() {
  Card_ascii temp;
  for (Card card : hidden_cards) {

  };
}

void display_card_ascii(Card card) {
  std::string suit;
  std::string rank;
  switch (card.value) {
  case Value::ACE:
    rank = " A";
  case Value::TWO:
    rank = " 2";
  case Value::THREE:
    rank = " 3";
  case Value::FOUR:
    rank = " 4";
  case Value::FIVE:
    rank = " 5";
  case Value::SIX:
    rank = " 6";
  case Value::SEVEN:
    rank = " 7";
  case Value::EIGHT:
    rank = " 8";
  case Value::NINE:
    rank = " 9";
  case Value::TEN:
    rank = "10";
  case Value::JACK:
    rank = " J";
  case Value::QUEEN:
    rank = " Q";
  case Value::KING:
    rank = " K";
  }
}
