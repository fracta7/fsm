#ifndef FRONTEND_H_
#define FRONTEND_H_

#include <ncurses.h>
#include <stdbool.h>

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

bool draw_state(GameInfo_t state, UserAction_t *event);

#endif  // FRONTEND_H_
