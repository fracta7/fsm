#include "backend.h"

void free_state(GameInfo_t *state) {
  for (int i = 0; i < 20; i++) {
    free(state->field[i]);
  }
  free(state->field);
  state->field = NULL;
  for (int i = 0; i < 4; i++) {
    free(state->next[i]);
  }
  free(state->next);
  state->next = NULL;
}

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
  state->field[18][5] = 2;
  state->field[17][5] = 2;
  state->field[16][5] = 2;
  state->field[17][4] = 2;
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

void handle_input(bool key_pressed, int *running, UserAction_t event,
                  GameInfo_t *state) {
  static int game_ended = 0;
  if (key_pressed) {
    switch (event) {
      case Terminate:
        if (game_ended)
          *running = 0;
        else
          game_ended = 1;
        break;
      case Action:
      case Left:
      case Right:
      case Down:
      case Up:
      case Start:
        if (state->pause == 0) update_state(state);
        break;
      case Pause:
        if (state->pause)
          state->pause = 0;
        else
          state->pause = 1;
        if (state->pause == 0) {
          update_state(state);
        }
        break;
      default:
        break;
    }
  }
}
