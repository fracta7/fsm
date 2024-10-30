#include "controller.h"

bool get_input(UserAction_t *event) {
  bool key_pressed = true;
  int ch = getch();

  // Process input
  switch (ch) {
    case KEY_UP:
      *event = Up;
      break;
    case KEY_DOWN:
      *event = Down;
      break;
    case KEY_LEFT:
      *event = Left;
      break;
    case KEY_RIGHT:
      *event = Right;
      break;
    case 'q':
    case 'Q':
      *event = Terminate;
      break;
    case 'p':
    case 'P':
      *event = Pause;
      break;
    case '\n':
      *event = Action;
      break;
    case 's':
    case 'S':
      *event = Start;
      break;
    case ERR:
    default:
      key_pressed = false;
      break;
  }
  return key_pressed;
}
