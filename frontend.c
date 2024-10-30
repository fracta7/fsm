#include "frontend.h"

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>

#include "fsm.h"

void draw_main_board_borders() {
  attron(COLOR_PAIR(1));
  mvprintw(0, 0, "                        ");
  attroff(COLOR_PAIR(1));
  for (int i = 1; i < 21; i++) {
    attron(COLOR_PAIR(1));
    mvprintw(i, 0, "  ");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(1));
    mvprintw(i, 21, "  ");
    attroff(COLOR_PAIR(1));
  }
  attron(COLOR_PAIR(1));
  mvprintw(21, 0, "                        ");
  attroff(COLOR_PAIR(1));
}

void draw_first_board_borders() {
  attron(COLOR_PAIR(1));
  mvprintw(0, 23, "                ");
  attroff(COLOR_PAIR(1));
  for (int i = 1; i < 7; i++) {
    // attron(COLOR_PAIR(1));
    // mvprintw(i, 23, " ");
    // attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(1));
    mvprintw(i, 37, "  ");
    attroff(COLOR_PAIR(1));
  }
  attron(COLOR_PAIR(1));
  mvprintw(7, 23, "                ");
  attroff(COLOR_PAIR(1));
}
void draw_second_board_borders() {
  for (int i = 8; i < 21; i++) {
    // attron(COLOR_PAIR(1));
    // mvprintw(i, 23, " ");
    // attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(1));
    mvprintw(i, 37, "  ");
    attroff(COLOR_PAIR(1));
  }
  attron(COLOR_PAIR(1));
  mvprintw(21, 23, "                ");
  attroff(COLOR_PAIR(1));
}

void draw_borders() {
  draw_main_board_borders();
  draw_first_board_borders();
  draw_second_board_borders();
}

void draw_field(GameInfo_t state) {
  if (state.field != NULL) {
    int shift_x = 2;
    int shift_y = 1;

    for (int i = 0; i < 20; i++) {
      for (int j = 0; j < 10; j++) {
        if (state.field[i][j] == 1) {
          attron(COLOR_PAIR(2));
          mvprintw(i + shift_y, j + j + shift_x, "  ");
          attroff(COLOR_PAIR(2));
        } else if (state.field[i][j] == 2) {
          attron(COLOR_PAIR(3));
          mvprintw(i + shift_y, j + j + shift_x, "[]");
          attroff(COLOR_PAIR(3));
        } else {
          mvprintw(i + shift_y, j + j + shift_x, "  ");
        }
      }
    }
  }
}

void draw_next(GameInfo_t state) {
  if (state.next != NULL) {
    int shift_x = 25;
    int shift_y = 2;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (state.next[i][j]) {
          attron(COLOR_PAIR(2));
          mvprintw(i + shift_y, j + j + shift_x, "  ");
          attroff(COLOR_PAIR(2));
        } else {
          mvprintw(i + shift_y, j + j + shift_x, "  ");
        }
      }
    }
  }
}

void draw_score(GameInfo_t state) {
  int shift_x = 25;
  int shift_y = 9;
  // score
  mvprintw(0 + shift_y, 0 + shift_x, "Score:");
  attron(COLOR_PAIR(3));
  attron(A_BOLD);
  mvprintw(1 + shift_y, 0 + shift_x, "%d", state.score);
  attroff(COLOR_PAIR(3));
  attroff(A_BOLD);

  // high score
  mvprintw(3 + shift_y, 0 + shift_x, "High Score:");
  attron(COLOR_PAIR(3));
  attron(A_BOLD);
  mvprintw(4 + shift_y, 0 + shift_x, "%d", state.high_score);
  attroff(COLOR_PAIR(3));
  attroff(A_BOLD);

  // level
  mvprintw(6 + shift_y, 0 + shift_x, "Level:");
  attron(COLOR_PAIR(3));
  attron(A_BOLD);
  mvprintw(7 + shift_y, 0 + shift_x, "%d", state.level);
  attroff(COLOR_PAIR(3));
  attroff(A_BOLD);

  // speed
  mvprintw(9 + shift_y, 0 + shift_x, "Speed:");
  attron(COLOR_PAIR(3));
  attron(A_BOLD);
  mvprintw(10 + shift_y, 0 + shift_x, "%d", state.speed);
  attroff(COLOR_PAIR(3));
  attroff(A_BOLD);
}

void draw_pause() {
  attron(COLOR_PAIR(4));
  mvprintw(11, 9, "Paused");
  attroff(COLOR_PAIR(4));
}

void draw_game_over() {
  attron(COLOR_PAIR(4));
  mvprintw(11, 7, "Game Over!");
  attroff(COLOR_PAIR(4));
}

void draw_help() {
  int y = 23;
  int x = 8;
  mvprintw(y, x, "         S - Start");
  mvprintw(y + 1, x, "         P - Pause");
  mvprintw(y + 2, x, "     ENTER - Action");
  mvprintw(y + 3, x, "         Q - Terminate");
  mvprintw(y + 4, x, "ARROW KEYS - Arrows Keys");
}

void draw_state(GameInfo_t state, UserAction_t event) {
  static bool paused = false;
  static bool game_over = false;

  draw_borders();
  draw_next(state);
  draw_score(state);
  draw_field(state);
  draw_help();

  if (event == Pause) paused = !paused;
  if (event == Terminate) game_over = true;
  if (game_over) draw_game_over();
  if (state.pause && !game_over) draw_pause();
  refresh();
}
