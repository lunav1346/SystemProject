#ifndef STUBS_H
#define STUBS_H

#include "game.h"

void spawn_food(object* o);
void draw_food(int y, int x, char* s);
void check_food(object* o, Stat* s);

void spawn_item(object* o);
void draw_item(int y, int x, char* s);
void check_item(object* o, Stat* s);

void spawn_obstacle(object* o);
void draw_obstacle(int y, int x, char* s);
void check_obstacle(object* o, Stat* s);

#endif