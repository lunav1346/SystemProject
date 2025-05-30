#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include "point.h"

int main() 
{   // ncurses 관련 초기화
    initscr(); // start, init ncurse
    cbreak();  // disable line break buffer
    nodelay(stdscr, TRUE); // no wait to wait for keyboard input
    noecho();  // do not show input char on screen
    curs_set(0); // do not show cursor  
    move(0, 0);
    
    player point1; // 포인트 관련 구조체

    spawn_point(&point1); // 포인트 구조체 초기화

    while(1){
        point(&point1); // 유저 입력 + 포인트 그리기 + 벽 충돌 확인
                        // w a s d 로 움직입니다 영어 소문자
        usleep(100000); 
    }

    endwin(); // end ncurse
    return 0;
}