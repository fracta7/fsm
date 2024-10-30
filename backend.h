#ifndef BACKEND_H_
#define BACKEND_H_
#include <stdlib.h>

#include "controller.h"
#include "frontend.h"
#include "fsm.h"

void handle_input(bool key_pressed, int *running, UserAction_t event,
                  GameInfo_t *state);
void free_state(GameInfo_t *state);
void init_state(GameInfo_t *state);

#endif  // BACKEND_H_
