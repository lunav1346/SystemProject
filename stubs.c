
#include <ncurses.h>
#include "game.h"

void spawn_food(object* o) {
    o->x = 10; o->y = 5;
}

void draw_food(int y, int x, char* s) {
    mvprintw(y, x, s);
}

void check_food(object* o, Stat* s) {}

void spawn_item(object* o) {
    o->x = 13; o->y = 8;
}

void draw_item(int y, int x, char* s) {
    mvprintw(y, x, s);
}

void check_item(object* o, Stat* s) {}

void spawn_obstacle(object* o) {
    o->x = 5; o->y = 10;
}

void draw_obstacle(int y, int x, char* s) {
    mvprintw(y, x, s);
}

void check_obstacle(object* o, Stat* s) {}
