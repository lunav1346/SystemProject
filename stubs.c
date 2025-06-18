
#include <ncurses.h>
#include "game.h"

void spawn_food(object* o) {
    o->x = 10; o->y = 5;
}

void draw_food(int y, int x, char* s) {
    mvprintw(y, x, "%s", s);
}

void check_food(object* o, Stat* s) {}
//item 부분 수정 ---> item 관련 모두 주석처리
// void spawn_item(object* o) {
//     o->x = 13; o->y = 8;
// }

// void draw_item(int y, int x, char* s) {
//     mvprintw(y, x, "%s", s);
// }

// void check_item(object* o, Stat* s) {}
