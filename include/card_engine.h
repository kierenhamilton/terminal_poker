#ifndef CARD_ENGINE_H
#define CARD_ENGINE_H
#include <string_view>
#include <vector>


enum class Value {
  ACE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  TEN,
  JACK,
  QUEEN,
  KING,
};

enum class Suit {
  SPADES,
  CLUBS,
  HEARTS,
  DIAMONDS,
};


struct Card {
  Value value{};
  Suit suit{};
};

std::string_view get_suit_name(const Suit suit);

std::string_view get_value_name(const Value value);

Card draw_card(std::vector<Card> &deck);

void display(std::vector<Card> &deck);

void display(Card &card);

void init_deck(std::vector<Card> &deck);

void shuffle(std::vector<Card> &deck);


#endif // !CARDS_H
