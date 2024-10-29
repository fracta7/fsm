#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>

#include "game.h"

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
  mvprintw(0, 23, "                 ");
  attroff(COLOR_PAIR(1));
  for (int i = 1; i < 7; i++) {
    attron(COLOR_PAIR(1));
    mvprintw(i, 23, " ");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(1));
    mvprintw(i, 38, "  ");
    attroff(COLOR_PAIR(1));
  }
  attron(COLOR_PAIR(1));
  mvprintw(7, 23, "                 ");
  attroff(COLOR_PAIR(1));
}
void draw_second_board_borders() {
  for (int i = 8; i < 21; i++) {
    attron(COLOR_PAIR(1));
    mvprintw(i, 23, " ");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(1));
    mvprintw(i, 38, "  ");
    attroff(COLOR_PAIR(1));
  }
  attron(COLOR_PAIR(1));
  mvprintw(21, 23, "                 ");
  attroff(COLOR_PAIR(1));
}

void draw_borders() {
  draw_main_board_borders();
  draw_first_board_borders();
  draw_second_board_borders();
}

void draw_field(GameInfo_t state) {
  int shift_x = 2;
  int shift_y = 1;
  if (state.field != NULL) {
    for (int i = 0; i < 20; i++) {
      for (int j = 0; j < 10; j++) {
        if (state.field[i][j]) {
          attron(COLOR_PAIR(2));
          mvprintw(i + shift_y, j + j + shift_x, "  ");
          attroff(COLOR_PAIR(2));
        }
      }
    }
  }
}

void draw_next(GameInfo_t state) {
  if (state.next != NULL) {
    int shift_x = 26;
    int shift_y = 2;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (state.next[i][j]) {
          attron(COLOR_PAIR(2));
          mvprintw(i + shift_y, j + j + shift_x, "  ");
          attroff(COLOR_PAIR(2));
        }
      }
    }
  }
}

void draw_score(GameInfo_t state) {
  int shift_x = 26;
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
  mvprintw(11, 8, "Paused");
  attroff(COLOR_PAIR(4));
}

bool handle_input(UserAction_t *event) {
  bool key_pressed = true;
  int ch = getch();  // Non-blocking input check

  // Process input
  switch (ch) {
    case KEY_UP:
      *event = Up;
      break;
    case KEY_DOWN:
      *event = Down;
      break;
    case KEY_LEFT:
      *event = Left;
      break;
    case KEY_RIGHT:
      *event = Right;
      break;
    case 'q':
    case 'Q':
      *event = Terminate;
      break;
    case 'p':
    case 'P':
      *event = Pause;
      break;
    case '\n':
      *event = Action;
      break;
    case 's':
    case 'S':
      *event = Start;
      break;
    case ERR:
    default:
      key_pressed = false;
      break;
  }

  refresh();
  return key_pressed;
}

bool draw_state(GameInfo_t state, UserAction_t *event) {
  static bool paused = false;
  // Initialize ncurses
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

  draw_borders();
  draw_next(state);
  draw_score(state);
  draw_field(state);

  bool result = handle_input(event);
  if (result && *event == Pause) {
    paused = !paused;
    if (!paused) {
      mvprintw(11, 8, "      ");
    }
  }
  if (paused) draw_pause();
  refresh();

  return result;
}
