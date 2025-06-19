#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "stubs.h"

extern player point1;

void spawn_food(object* food) {
    static bool seeded = false;
    if (!seeded) {
        srand(time(NULL));
        seeded = true;
    }

    food->x = rand() % WIDTH;
    food->y = (rand() % (HEIGHT - 3)) + 3;  // 상단 UI 영역(3줄) 피하기
    food->type = 'F';
    food->symbol = '*';
    food->isHit = false;
}

void draw_food(int y, int x, char* symbol) {
    mvprintw(y, x, "%s", symbol);
}

void check_food(object* food, Stat* stat) {
    if (point1.x == food->x && point1.y == food->y) {
        stat->score++;
        spawn_food(food);
    }
}
