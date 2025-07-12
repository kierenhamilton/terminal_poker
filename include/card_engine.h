#ifndef CARD_ENGINE_H
#define CARD_ENGINE_H
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

enum class Value : uint32_t {
  TWO=2,
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
  ACE,
};

enum class Suit {
  SPADES,
  CLUBS,
  HEARTS,
  DIAMONDS,
};

struct Card_ascii {
  Card_ascii () : line1(""), line2(""), line3(""), line4(""), line5("") {};
  std::string line1;
  std::string line2;
  std::string line3;
  std::string line4;
  std::string line5;
  std::string line6;

  Card_ascii operator+(Card_ascii &card_ascii) {
    Card_ascii temp;

    temp.line1 = line1 + " " + card_ascii.line1;
    temp.line2 = line2 + " " + card_ascii.line2;
    temp.line3 = line3 + " " + card_ascii.line3;
    temp.line4 = line4 + " " + card_ascii.line4;
    temp.line5 = line5 + " " + card_ascii.line5;
    temp.line6 = line6 + " " + card_ascii.line6;

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

void display_card_ascii(const Card_ascii &card, std::string s);

Card_ascii get_card_ascii(Card &card);

Card_ascii get_face_down_ascii();

void display(std::vector<Card> &deck);

void display(Card &card);

void init_deck(std::vector<Card> &deck);

void shuffle(std::vector<Card> &deck);

#endif // !CARDS_H
