#ifndef FSM_H_
#define FSM_H_
#include <stdbool.h>
#include <stdlib.h>

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

void game_loop();

#endif  // FSM_H_
