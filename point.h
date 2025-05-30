#ifndef POINT_H
#define POINT_H

// 이 헤더파일 내용은 나중에 한 헤더파일로 합칠 예정? 입니다

#define WIDTH 80 
#define HEIGHT 24

typedef struct {// point의 정보에 관한 구조체
    int x;      // 좌표 유의 사항 : 아래로 내려갈 수록 y가 + 됨. 주의!
    int y;
    char dir;   // 포인트가 계속 움직일 방향, 초기값은 ' '.
                //.... 더 추가 될 수 있음
}player;        

void point(player*);   // 유저의 입력을 받고, 포인트를 이동, 그림, player 구조체 포인터만 인자로 넣어주면 됩니다!
void spawn_point(player*); // 포인트 초기화
void draw_point(int, int, char*);   // 좌표값에 포인트를 그림
void check_point(player*); // 포인트 벽 충돌, 오버플로우 방지
                           // 우선 벽은 헤더파일에 적힌 터미널 사이즈로 해두었습니다

#endif