#include "card_engine.h"
#include <algorithm>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string_view>


std::string_view get_suit_name(const Suit suit) {
  switch (suit) {
  case Suit::SPADES:
    return "SPADES";
  case Suit::CLUBS:
    return "CLUBS";
  case Suit::HEARTS:
    return "HEARTS";
  case Suit::DIAMONDS:
    return "DIAMONDS";
  default:
    return "???";
  }
}

std::string_view get_value_name(const Value value) {
  switch (value) {
  case Value::ACE:
    return "ACE";
  case Value::TWO:
    return "TWO";
  case Value::THREE:
    return "THREE";
  case Value::FOUR:
    return "FOUR";
  case Value::FIVE:
    return "FIVE";
  case Value::SIX:
    return "SIX";
  case Value::SEVEN:
    return "SEVEN";
  case Value::EIGHT:
    return "EIGHT";
  case Value::NINE:
    return "NINE";
  case Value::TEN:
    return "TEN";
  case Value::JACK:
    return "JACK";
  case Value::QUEEN:
    return "QUEEN";
  case Value::KING:
    return "KING";
  default:
    return "???";
  }
}
void display(std::vector<Card> &deck) {
  for (Card &temp : deck)
  {
    std::cout << get_value_name(temp.value) << " " << get_suit_name(temp.suit)
              << std::endl;
  }
}

void display(Card & card)
{

  std::cout << get_value_name(card.value) << " " << get_suit_name(card.suit)
    << std::endl;
}

void init_deck(std::vector<Card> &deck) {
  deck.clear();
  for (int s{0}; s < 4; s++)
    for (int v{0}; v < 13; v++) {
      deck.push_back({static_cast<Value>(v), static_cast<Suit>(s)});
    }
}

void shuffle(std::vector<Card> &deck) {
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(deck.begin(), deck.end(), g);
};

Card draw_card(std::vector<Card> &deck) {

  if (deck.empty())
    throw std::out_of_range("cannot draw form an empty deck");
  Card temp{std::move(deck.back())};
  deck.pop_back();
  return temp;
}
