#include "stubs.h"  // 또는 food.h
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

extern player point1;
extern object items[];               // 아이템 배열
extern const int item_num;

extern object get_obstacle_array();  // 또는 extern access 방법 따로 정의 필요
extern const int max_obstacles;     // 최대 장애물 수

void spawn_food(object* food) {
    static bool seeded = false;
    if (!seeded) {
        srand(time(NULL));
        seeded = true;
    }

    int new_x, new_y;
    int attempts = 0;
    const int max_attempts = 100;

    while (1) {
        new_x = rand() % WIDTH;
        new_y = (rand() % (HEIGHT - 3)) + 3;

        bool conflict = false;

        // 아이템 위치 체크
        for (int i = 0; i < item_num; i++) {
            if (items[i].x == new_x && items[i].y == new_y) {
                conflict = true;
                break;
            }
        }
        if (conflict) {
            attempts++;
            if (attempts > max_attempts) break;
            else continue;
        }

        // 장애물 위치 체크
        for (int i = 0; i < max_obstacles; i++) {
            if (!obstacles[i].active) continue;

            if (obstacles[i].orientation == 1) { // vertical
                for (int j = 0; j < 5; j++) {
                    if (new_x == obstacles[i].obj.x &&
                        new_y == obstacles[i].obj.y + j) {
                        conflict = true;
                        break;
                    }
                }
            } else { // horizontal
                for (int j = 0; j < 15; j++) {
                    if (new_y == obstacles[i].obj.y &&
                        new_x == obstacles[i].obj.x + j) {
                        conflict = true;
                        break;
                    }
                }
            }
            if (conflict) break;
        }
        if (conflict) {
            attempts++;
            if (attempts > max_attempts) break;
            else continue;
        }

        // 충돌 없으면 루프 종료
        break;
    }


    food->x = new_x;
    food->y = new_y;
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
