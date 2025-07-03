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
  for (Card &temp : deck) {
    std::cout << get_value_name(temp.value) << " " << get_suit_name(temp.suit)
              << std::endl;
  }
}

Card_ascii get_face_down_ascii(){
  Card_ascii temp;
  temp.line1 = "+=====+";
  temp.line2 = "|=+=+=|";
  temp.line3 = "|+=+=+|";
  temp.line4 = "|=+=+=|";
  temp.line5 = "|+=+=+|";
  temp.line6 = "+=====+";
}

Card_ascii get_card_ascii(Card &card) {
  Card_ascii temp;
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
  };
  switch (card.suit) {
  case Suit::CLUBS:
    suit = "♣";
  case Suit::DIAMONDS:
    suit = "♦";
  case Suit::HEARTS:
    suit = "♥";
  case Suit::SPADES:
    suit = "♠";
  };
  temp.line1 = "+=====+";
  temp.line2 = "|" + rank + "  " + suit + "|";
  temp.line3 = "|     |";
  temp.line4 = "|     |";
  temp.line5 = "|" + suit + "  " + rank + "|";
  temp.line6 = "+=====+";

  return temp;
}

void display_card_ascii(const Card_ascii &card) {
  std::cout << card.line1;
  std::cout << card.line2;
  std::cout << card.line3;
  std::cout << card.line4;
  std::cout << card.line5;
  std::cout << card.line6;
}

void display(Card &card) {

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
