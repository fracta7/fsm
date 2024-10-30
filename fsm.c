#include "fsm.h"

#include "backend.h"
#include "frontend.h"

void game_loop(InputHandlerCallback callback) {
  GameInfo_t state;
  UserAction_t event;
  int running = 1;
  init_state(&state);

  initscr();  // Start ncurses mode
  start_color();
  cbreak();              // Disable line buffering, pass on everything
  noecho();              // Do not print user input
  keypad(stdscr, TRUE);  // Enable special keys (e.g., arrow keys)
  nodelay(stdscr, TRUE);
  curs_set(FALSE);

  init_pair(1, COLOR_WHITE, COLOR_WHITE);  // Text white, background blue
  init_pair(2, COLOR_BLUE, COLOR_BLUE);    // Text white, background blue
  init_pair(3, COLOR_GREEN, COLOR_BLACK);
  init_pair(4, COLOR_WHITE, COLOR_RED);
  init_pair(5, COLOR_WHITE, COLOR_BLACK);
  while (running) {
    bool key_pressed = get_input(&event);
    callback(key_pressed, &running, event, &state);
    draw_state(state, event);
  }

  endwin();
  free_state(&state);
}
