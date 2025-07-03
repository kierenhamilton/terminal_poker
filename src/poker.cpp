#include <vector>
#include "card_engine.h"
#include "poker.h"


void Game::setup() {
  init_deck(deck);
  shuffle(deck);
  for (int i = 0; i < 5; i++)
    hidden_cards.push_back(draw_card(deck));

  for (int i = 0; i < 2; i++){

    for (Player& player : players){
      player.set_player_hand(draw_card(deck));
    }
  }
}

