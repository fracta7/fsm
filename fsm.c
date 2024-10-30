#include "fsm.h"

#include "backend.h"
#include "frontend.h"

void game_loop() {
  GameInfo_t state;
  UserAction_t event;
  int running = 1;
  init_state(&state);
  while (running) {
    bool key_pressed = get_input(&event);
    handle_input(key_pressed, &running, event, &state);
    draw_state(state, event);
  }
  endwin();
  free_state(&state);
}
