#ifndef FRONTEND_H_
#define FRONTEND_H_

#include <ncurses.h>
#include <stdbool.h>

#include "fsm.h"

void draw_state(GameInfo_t state, UserAction_t event);

#endif  // FRONTEND_H_
