#include <ncurses.h>
#include <unistd.h>
#include "game.h"

void point(player *pt){
    char ch = getch();  // getch <- 입력 받아옴, 없어도 아래 코드 진행

    if (ch =='w')        pt->dir = 'w';
    else if (ch =='s')   pt->dir = 's';
    else if (ch =='a')   pt->dir = 'a';
    else if (ch =='d')  pt->dir = 'd';
    

    draw_point(pt->y, pt->x, " "); // 움직이기 전 좌표의 point를 지움

    move_point(pt); // 아래 스위치 문을 어셈블리로 구현한 함수, point.s에 정의됨
    /*
    switch (pt->dir)
    {
    case 'w' :
        pt->y--;
        break;
    case 's' :
        pt->y++;
        break;
    case 'a' :
        pt->x--;
        break;
    case 'd' :
        pt->x++;
        break;
    default:
        break;
    }
    */
    check_point(pt);                        // 충돌 확인
    draw_point(pt->y, pt->x, "@");          // point 그림
    return;
}

void spawn_point(player* pt){ 
    pt->x = 0;
    pt->y = 0;
    pt->dir = ' ';                          // 포인트가 계속 진행할 방향
}

void draw_point(int y, int x, char* str){
    mvprintw(y, x, "%s", str);
}


void check_point(player *pt){
    if (pt->x < 0) pt->x = 0;               // 충돌, 오버플로우 방지
    if (pt->x >= WIDTH) pt->x = WIDTH - 1;  // 화면 사이즈는 point.h에 정의됨
    if (pt->y < 0) pt->y = 0;
    if (pt->y >= HEIGHT) pt->y = HEIGHT - 1;
}