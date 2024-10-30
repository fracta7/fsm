#ifndef FSM_H_
#define FSM_H_
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

typedef void (*InputHandlerCallback)(bool key_pressed, int *running,
                                     UserAction_t event, GameInfo_t *state);

void game_loop(InputHandlerCallback callback);

#endif  // FSM_H_
