#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"               // 게임 관련 헤더 파일

#define GAME_DURATION 60        // 게임 시간
#define FRAME_DELAY 100         // 프레임 딜레이 (밀리초 단위)
#define ITEM_NUM 3              // 아이템 개수를 관리하기 위한 매크로

player point1;                  // 플레이어 포인트 초화
const int item_num = ITEM_NUM;  // extern으로 쓰기 위해 const 변수화
object items[ITEM_NUM];

bool immortal = false;          // '무적' 아이템의 상태를 공유하기 위한 전역 변수들
time_t immortal_end; 
bool game_over = false;         // '게임 종료' 여부 판단을 위한 변수

// 화면 테두리(벽) 그리기 함수
void draw_wall() {     
    for (int x = 0; x < WIDTH; x++) {
        mvaddch(0, x, '#');                 // 위쪽 벽
        mvaddch(HEIGHT - 1, x, '#');        // 아래쪽 벽
    }
    for (int y = 0; y < HEIGHT; y++) {
        mvaddch(y, 0, '#');                 // 왼쪽 벽
        mvaddch(y, WIDTH - 1, '#');         // 오른쪽 벽
    }
}

// 벽과 부딪혔는지 확인하는 함수
void check_wall() {
    if (point1.x <= 0 || point1.x >= WIDTH - 1 ||
        point1.y <= 0 || point1.y >= HEIGHT - 1) {
        game_over = true;
    }
}

int main() {
    srand(time(NULL));              // 랜덤 시드 설정
    initscr();                      // ncurese 초기화
    cbreak();                       // 라인 버퍼 없이 입력 처리
    noecho();                       // 키안보이게
    curs_set(0);                    // 커서안보이게
    nodelay(stdscr, TRUE);          
    timeout(FRAME_DELAY);           // geth 대기 시간 설정

    time_t start_time = time(NULL);     // 게임 시작 시간
    time_t now;                         // 현재 시간

    Stat stat = { .score = 0 };     // 점수 상태 구조체 초기화
    object food, obstacle;          // 음식, 장애물 선언

    spawn_point(&point1);           // 플레이어 포인트 스폰


    for (int i = 0; i < item_num; i++) {    // 아이템 하나만 생성하던 것을, 반복문을 통해 3개 생성하도록 변경
        spawn_item(&items[i]);
    }

    spawn_food(&food);              // 음식 오브젝트 스폰
    draw_wall();                    // 벽 표시
    draw_point(point1.y, point1.x, "@"); // 초기 플레이어 표시



    // 메인 게임 루프 
    while (1) {
        now = time(NULL);                   // 현재 시간 갱신
        int remaining = GAME_DURATION - (now - start_time); // 남은 시간 게산
        if (remaining <= 0 || game_over) break;     // 시간 끝났거나 게임 오버면 종료

        // 상단에 게임 상태 출력 (남은 시간, 점수, 플레이어 위치)
        mvprintw(0, 0, "TIME : %2dsec", remaining);     
        mvprintw(1, 0, "SCORE : %d", stat.score);       
        mvprintw(2, 0, "POINT : (%d, %d)", point1.y, point1.x);

        point(&point1); // 플레이어 이동

        // '무적' 상태를 확인하고, 시간이 다 되면 해제하며, 플레이어 심볼을 바꾸는 로직
        if (immortal) {
            if (time(NULL) > immortal_end) {
                immortal = false;
                draw_point(point1.y, point1.x, "@");
            } else {
                draw_point(point1.y, point1.x, "S");       // 무적상태일 때는 플레이어 s로 표시
            }
        }

        spawn_obstacle(&obstacle);      // 장애물 오브젝트 스폰
        draw_food(food.y, food.x, "*"); // 음식 오브젝트 그리기

        // 아이템 3개 그리기
        for (int i = 0; i < item_num; i++) {
            draw_item(items[i].y, items[i].x, "?");
        }
        
        draw_obstacle(obstacle.y, obstacle.x, "^"); // 장애물 그리기

    
        check_food(&food, &stat); // 음식과 충돌 체크
        

        // 아이템 3개 충돌 체크
        for (int i = 0; i < item_num; i++) {
            check_item(&items[i], &point1, &immortal, &immortal_end);
        }

        check_obstacle(&obstacle); // 장애물과 충돌 체크
        check_wall();   // 벽과 충돌 체크 

        refresh();
    }

    clear();
    if (game_over) {
        mvprintw(HEIGHT / 2 - 1, (WIDTH - 20) / 2, "GAME OVER!"); // 벽 충돌 종료
    } else {
        mvprintw(HEIGHT / 2 - 1, (WIDTH - 15) / 2, "TIME OVER!"); // 시간 초과 종료
    }
    mvprintw(HEIGHT / 2, (WIDTH - 20) / 2, "SCORE : %d", stat.score);   // 최종 점수 출력
    refresh();
    sleep(3);       // 3초 대기 후에 종료

    endwin();       // ncruses 종료
    return 0;
}
