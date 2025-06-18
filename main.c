#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "game.h" // 게임 관련 헤더 파일
#include "stubs.h" // 임시용 함수 선언모음집

#define GAME_DURATION 60    // 게임 시간 
#define FRAME_DELAY 100 // 프레임 딜레이
#define item_num 3 // item 부분 수정 ---> 변경: 아이템 개수를 관리하기 위한 매크로 추가

player point1;
// item부분 수정 --> 추가: '무적' 아이템의 상태를 공유하기 위한 전역 변수들
bool immutable = false;
time_t immutable_end;

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
    object food, item[item_num], obstacle; // 게임 오브젝트들   item 부분 수정 item -> item[item_num]으로 수정

    spawn_point(&point1); // 플레이어 포인트 스폰
    spawn_food(&food); // 음식 오브젝트 스폰
    for (int i = 0; i < item_num; i++) {  //item부분수정 --> 변경: 아이템 하나만 생성하던 것을, 반복문을 통해 3개 생성하도록 변경
        spawn_item(&item[i]); // 아이템 오브젝트 스폰
    }
    draw_point(point1.y, point1.x, "@"); // 초기 위치 강제 출력

    while (1) {
        now = time(NULL); // 현재 시간 갱신
        int remaining = GAME_DURATION - (now - start_time); // 남은 시간 계산
        if (remaining <= 0) break; // 게임 시간이 끝나면 루프 종료

        mvprintw(0, 0, "TIME : %2dsec", remaining); // 남은 시간 출력
        mvprintw(1, 0, "SCORE : %d", stat.score); // 현재 점수 출력
        mvprintw(2, 0, "POINT : (%d, %d)", point1.y, point1.x); // 현재 포인트 위치 출력

        // item 부분 수정 --> 추가: '무적' 상태를 확인하고, 시간이 다 되면 해제하며, 플레이어 심볼을 바꾸는 로직
        if (immutable) {
            if (time(NULL) > immutable_end) {
                immutable = false;
                draw_point(point1.y, point1.x, "@");
            } else {
                draw_point(point1.y, point1.x, "S");
            }
        }

        point(&point1); // 플레이어 포인트 업데이트
        spawn_obstacle(&obstacle); // 장애물 오브젝트 스폰

        draw_food(food.y, food.x, "*"); // 음식 오브젝트 그리기
        // item 부분 수정 --> 변경: 아이템 하나만 그리던 것을, 반복문을 통해 3개 모두 그리도록 변경
        for (int i = 0; i < item_num; i++) {
            draw_item(items[i].y, items[i].x, "?"); 
        }
        draw_obstacle(obstacle.y, obstacle.x, "^"); // 장애물 오브젝트 그리기

        check_food(&food, &stat); // 음식 오브젝트 충돌 체크
        // item 부분 수정 --> 변경: 아이템 하나만 충돌 검사하던 것을, 반복문을 통해 3개 모두 검사하도록 변경
        for (int i = 0; i < item_num; i++) {
            check_item(&items[i], &stat); 
        }
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
