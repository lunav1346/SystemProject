#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

// ==========================
// 점수 구조체 (가장 위에 배치)
// ==========================
typedef struct Stat {
    int score;
} Stat;

// ==========================
// 화면 크기 (고정)
// ==========================
#define WIDTH 80 
#define HEIGHT 24

// ==========================
// 플레이어 구조체 및 함수
// ==========================
typedef struct {
    int x;
    int y;
    char dir;
} player;

void point(player*);
void spawn_point(player*);
void draw_point(int, int, char*);
void check_point(player*);

// ==========================
// 오브젝트 구조체 및 함수
// ==========================
typedef struct {
    int x;
    int y;
    char type;    // 'F', 'I', 'O'
    char symbol;  // '*', '?', '^'
    bool isHit;
} object;

void spawn_food(object*);
void draw_food(int, int, char*);
void check_food(object*, Stat*);

void spawn_item(object*);
void draw_item(int, int, char*);
void check_item(object*, Stat*);

void spawn_obstacle(object*);
void draw_obstacle(int, int, char*);
void check_obstacle(object*, Stat*);

#endif // GAME_H
