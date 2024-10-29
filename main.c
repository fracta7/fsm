#include <stdlib.h>

#include "frontend.h"

void fill_field(GameInfo_t *state) {
  state->field[2][5] = 1;
  state->field[3][5] = 1;
  state->field[3][4] = 1;
  state->field[4][5] = 1;

  for (int i = 0; i < 6; i++) {
    state->field[19][i] = 1;
  }
  for (int i = 0; i < 5; i++) {
    state->field[18][i] = 1;
  }
}

void init_state(GameInfo_t *state) {
  state->field = (int **)calloc(20, sizeof(int *));
  for (int i = 0; i < 20; i++) {
    state->field[i] = (int *)calloc(10, sizeof(int));
  }
  state->next = (int **)calloc(4, sizeof(int *));
  for (int i = 0; i < 4; i++) {
    state->next[i] = (int *)calloc(4, sizeof(int));
  }
  state->next[1][1] = 1;
  state->next[2][1] = 1;
  state->next[2][2] = 1;
  state->next[2][3] = 1;
  state->score = 600;
  state->high_score = 1200;
  state->level = 2;
  state->speed = 3;
  state->pause = 0;
  fill_field(state);
}

void update_state(GameInfo_t *state) {
  state->score++;
  state->level++;
  state->speed++;
  state->high_score++;
}

int main() {
  GameInfo_t state;
  UserAction_t event;
  int running = 1;
  init_state(&state);
  while (running) {
    bool key_pressed = draw_state(state, &event);
    if (key_pressed) {
      switch (event) {
        case Terminate:
          running = 0;
          break;
        case Action:
        case Left:
        case Right:
        case Down:
        case Up:
        case Start:
        case Pause:
          update_state(&state);
          break;
        default:
          break;
      }
    }
  }
  endwin();
  return 0;
}
