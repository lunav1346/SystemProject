#ifndef OBJECT_H
#define OBJECT_H

#include <stdbool.h>

typedef struct {
	int x; 
	int y;
	char type; // F: Foods, I: Items, O: Obstacles
	char symbol; // F: *, I: ?, O: ^
	bool isHit; // Check Collision, Default is false
}object;

// function prototype
// May be Add


void spawn_food(object*);
void draw_food(int, int, char*);
void check_food(object*);

void spawn_item(object*);
void draw_item(int, int, char*);
void check_item(object*);

void spawn_obstacle(object*);
void draw_obstacle(int, int, char*);
void check_obstacle(object*);


#endif
