#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <time.h> //item파트 수정
extern bool immortal; //item파트 수정
extern time_t immortal_end; //item파트 수정

// 오브젝트 구조체 및 함수

typedef struct {
    int x;
    int y;
    char type;    // 'F', 'I', 'O'
    char symbol;  // '*', '?', '^'
    bool isHit;
} object;

// ObstacleData 정의
typedef struct {
    object obj;
    int orientation;
    bool active;
} ObstacleData;

extern ObstacleData obstacles[];
extern const int max_obstacles;

typedef struct Stat {
    int score;
} Stat;


#define WIDTH 80
#define HEIGHT 24

// 플레이어 구조체 및 함수

typedef struct {
    int x;
    int y;
    char dir;
} player;

void point(player*);
void spawn_point(player*);
void move_point(player*);
void draw_point(int, int, char*);
void check_point(player*);

void spawn_food(object*);
void draw_food(int, int, char*);
void check_food(object*, Stat*);

void spawn_item(object*);
void draw_item(int, int, char*);
void check_item(object*, player* p, bool* is_immortal, time_t* end_time);

void spawn_obstacle(object*);
void draw_obstacle(int, int, char*);
void check_obstacle(object*);

#endif // GAME_H
