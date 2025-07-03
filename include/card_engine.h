#ifndef CARD_ENGINE_H
#define CARD_ENGINE_H
#include <string>
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

struct Card_ascii {
  std::string line1;
  std::string line2;
  std::string line3;
  std::string line4;
  std::string line5;
  std::string line6;

  Card_ascii operator+(Card_ascii &card_ascii) {
    Card_ascii temp;

    temp.line1 = line1 += " " + card_ascii.line1;
    temp.line2 = line2 += " " + card_ascii.line2;
    temp.line3 = line3 += " " + card_ascii.line3;
    temp.line4 = line4 += " " + card_ascii.line4;
    temp.line5 = line5 += " " + card_ascii.line5;
    temp.line6 = line6 += " " + card_ascii.line6;

    return temp;
  }
};

struct Card {
  Value value{};
  Suit suit{};
};

std::string_view get_suit_name(const Suit suit);

std::string_view get_value_name(const Value value);

Card draw_card(std::vector<Card> &deck);

void get_card_ascii(Card &card);

void display(std::vector<Card> &deck);

void display(Card &card);

void init_deck(std::vector<Card> &deck);

void shuffle(std::vector<Card> &deck);

#endif // !CARDS_H
