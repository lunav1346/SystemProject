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

#endif
