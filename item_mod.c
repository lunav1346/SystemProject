#include <ncurses.h>
#include <stdlib.h> 
#include <time.h>   
#include "game.h"

// main.c에 정의된 전역 변수들을 참조


// 이 함수는 '하나'의 아이템을 랜덤 위치에 생성하는 역할
void spawn_item(object* item) {
   
    int new_x, new_y;
    int attempts = 0; // 무한 루프 방지를 위한 시도 횟수

    // 장애물('^')과 겹치지 않는 안전한 위치를 찾을 때까지 반복
    do {
        // 상단 UI 영역(3줄)을 피해 랜덤 위치 지정
        new_x = rand() % WIDTH;
        new_y = (rand() % (HEIGHT - 3)) + 3;
        attempts++;
        if (attempts > 100) { // 100번 시도 후에도 못 찾으면 그냥 마지막 위치에 생성
            return;
        }
    } while ((mvinch(new_y, new_x) & A_CHARTEXT) == '^');
    
    item->x = new_x;
    item->y = new_y;
    item->type = 'I';
    item->symbol = '?';
    item->isHit = false;
}

// 이 함수는 '하나'의 아이템을 그리는 단순한 역할
void draw_item(int y, int x, char* symbol) {
    mvprintw(y, x, "%s", symbol);
}

// 이 함수는 '하나'의 아이템 충돌만 검사하는 역할
void check_item(object* item, player* p, bool* immortal, time_t* immortal_end) {
    // 플레이어와 이 아이템의 좌표가 겹치는지 확인
    if (p->x == item->x && p->y == item->y) {
        
        // 무적 상태 활성화
        *immortal = true;
        *immortal_end = time(NULL) + 5;

        // 먹어 없어진 '이 아이템' 하나만 새로 스폰
        spawn_item(item);
    }
}
