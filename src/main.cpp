#include "card_engine.h"
#include "poker.h"
#include <vector>


int main() {

  std::vector<Card> deck;

  init_deck(deck);

  Card a = draw_card(deck);
  Card b = draw_card(deck);

  Card_ascii test = get_card_ascii(a);
  Card_ascii test2 = get_card_ascii(b);
  Card_ascii test4 = get_face_down_ascii();

  display(a);
  display(b);


  display_card_ascii(test);
  display_card_ascii(test2);
  display_card_ascii(test4);

  Card_ascii test3 = test + test2;

  test4 = test4 + test3;


  display_card_ascii(test3);
  display_card_ascii(test4);

  return 0;
}
