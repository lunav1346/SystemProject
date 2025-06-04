#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "game.h" // 게임 관련 헤더 파일
#include "stubs.h" // 임시용 함수 선언모음집

#define GAME_DURATION 60    // 게임 시간 
#define FRAME_DELAY 100 // 프레임 딜레이

player point1;

int main() {
    initscr(); // ncurses 초기화
    cbreak();  // 입력을 즉시 처리
    noecho(); // 입력을 화면에 출력하지 않음
    curs_set(0); // 커서 숨김
    nodelay(stdscr, TRUE); // getch()가 블록되지 않도록 설정
    timeout(FRAME_DELAY); // getch()의 타임아웃 설정

    time_t start_time = time(NULL); // 게임 시작 시간
    time_t now;  

    Stat stat = { .score = 0 }; // 게임 상태 초기화

    // player point1; // 플레이어 포인트 초기화
    object food, item, obstacle; // 게임 오브젝트들

    spawn_point(&point1); // 플레이어 포인트 스폰
    spawn_food(&food); // 음식 오브젝트 스폰
    spawn_item(&item); // 아이템 오브젝트 스폰

    draw_point(point1.y, point1.x, "@"); // 초기 위치 강제 출력

    while (1) {
        now = time(NULL); // 현재 시간 갱신
        int remaining = GAME_DURATION - (now - start_time); // 남은 시간 계산
        if (remaining <= 0) break; // 게임 시간이 끝나면 루프 종료

        mvprintw(0, 0, "TIME : %2dsec", remaining); // 남은 시간 출력
        mvprintw(1, 0, "SCORE : %d", stat.score); // 현재 점수 출력
        mvprintw(2, 0, "POINT : (%d, %d)", point1.y, point1.x); // 현재 포인트 위치 출력

        point(&point1); // 플레이어 포인트 업데이트
        spawn_obstacle(&obstacle); // 장애물 오브젝트 스폰

        draw_food(food.y, food.x, "*"); // 음식 오브젝트 그리기
        draw_item(item.y, item.x, "?"); // 아이템 오브젝트 그리기
        draw_obstacle(obstacle.y, obstacle.x, "^"); // 장애물 오브젝트 그리기

        check_food(&food, &stat); // 음식 오브젝트 충돌 체크
        check_item(&item, &stat); // 아이템 오브젝트 충돌 체크
        check_obstacle(&obstacle); // 장애물 오브젝트 충돌 체크

        refresh();  // 화면 업데이트
    }

    clear();
    mvprintw(HEIGHT / 2 - 1, (WIDTH - 15) / 2, "TIME OVER!"); // 게임 종료 메시지
    mvprintw(HEIGHT / 2, (WIDTH - 20) / 2, "SCORE : %d", stat.score); // 최종 점수 출력
    refresh();  
    sleep(3); // 3초 대기

    endwin(); // ncurses 종료
    return 0;  
}
