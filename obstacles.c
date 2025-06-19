#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "game.h"
#define MAX_OBSTACLES 25

extern player point1;

const int max_obstacles=MAX_OBSTACLES;

ObstacleData obstacles[MAX_OBSTACLES];
static int spawn_counter = 0;
static const int SPAWN_INTERVAL = 30;  // Spawn new obstacle every 30 frames
static bool initialized = false;
static bool first_spawn = true;

// spawn_obstacle >> AI가 짠 부분
void spawn_obstacle(object* obs) {
    if (!initialized) {
        srand(time(NULL));
        for(int i = 0; i < MAX_OBSTACLES; i++) {
            obstacles[i].active = false;
        }
        initialized = true;
    }
    
    // Always increment counter
    spawn_counter++;
    
    // Check if it's time to spawn a new obstacle
    if (spawn_counter >= SPAWN_INTERVAL || first_spawn) {
        spawn_counter = 0;
        
        // Find an inactive obstacle slot
        int new_idx = -1;
        for(int i = 0; i < MAX_OBSTACLES; i++) {
            if(!obstacles[i].active) {
                new_idx = i;
                break;
            }
        }
        
        if(new_idx != -1) {
            obstacles[new_idx].active = true;
            obstacles[new_idx].orientation = rand() % 2;
            
            // Spawn with safe distance from player
            int attempts = 0;
            do {
                if(obstacles[new_idx].orientation == 1) { // vertical
                    obstacles[new_idx].obj.x = rand() % 76;  // 80-5+1
                    obstacles[new_idx].obj.y = rand() % 20;  // 24-5+1
                } else { // horizontal
                    obstacles[new_idx].obj.x = rand() % 76;  // 80-5+1
                    obstacles[new_idx].obj.y = rand() % 22;  // 24-3+1
                }
                attempts++;
            } while(attempts < 10 && 
                    ((abs(obstacles[new_idx].obj.x - point1.x) < 5 && 
                      abs(obstacles[new_idx].obj.y - point1.y) < 5) ||
                     (obstacles[new_idx].orientation == 1 && 
                      obstacles[new_idx].obj.x == point1.x &&
                      point1.y >= obstacles[new_idx].obj.y && 
                      point1.y < obstacles[new_idx].obj.y + 5) ||
                     (obstacles[new_idx].orientation == 0 && 
                      obstacles[new_idx].obj.y == point1.y &&
                      point1.x >= obstacles[new_idx].obj.x && 
                      point1.x < obstacles[new_idx].obj.x + 5)));
            
            obstacles[new_idx].obj.type = 'O';
            obstacles[new_idx].obj.symbol = '^';
            obstacles[new_idx].obj.isHit = false;
            
            first_spawn = false;
        }
    }
    
    // Copy first active obstacle info to obs parameter
    for(int i = 0; i < MAX_OBSTACLES; i++) {
        if(obstacles[i].active) {
            *obs = obstacles[i].obj;
            break;
        }
    }
}

void draw_obstacle(int y, int x, char* symbol) {
    // Draw all active obstacles
    for(int i = 0; i < MAX_OBSTACLES; i++) {
        if(obstacles[i].active) {
            if(obstacles[i].orientation == 1) { // vertical
                for(int j = 0; j < 5; j++) {
                    if(obstacles[i].obj.y + j < 24) {
                        mvprintw(obstacles[i].obj.y + j, obstacles[i].obj.x, "%s", symbol);
                    }
                }
            } else { // horizontal
                for(int j = 0; j < 15; j++) {
                    if(obstacles[i].obj.x + j < 80) {
                        mvprintw(obstacles[i].obj.y, obstacles[i].obj.x + j, "%s", symbol);
                    }
                }
            }
        }
    }
}

void check_obstacle(object* obs) {

    //item부분 수정 -->(if문 추가)
    if (immutable){
        return;
    }  
    
    // Check collision with all active obstacles
    for(int i = 0; i < MAX_OBSTACLES; i++) {
        if(obstacles[i].active) {
            bool hit = false;
            
            if(obstacles[i].orientation == 1) { // vertical
                if(point1.x == obstacles[i].obj.x && 
                   point1.y >= obstacles[i].obj.y && 
                   point1.y < obstacles[i].obj.y + 5) {
                    hit = true;
                }
            } else { // horizontal
                if(point1.y == obstacles[i].obj.y && 
                   point1.x >= obstacles[i].obj.x && 
                   point1.x < obstacles[i].obj.x + 15) {
                    hit = true;
                }
            }
            
            if(hit) {
                clear();
                mvprintw(HEIGHT/2, WIDTH/2 - 5, "GAME OVER!");
                refresh();
                sleep(2);
                endwin();
                exit(0);
            }
        }
    }
}
