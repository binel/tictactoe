#ifndef t_game_h
#define t_game_h

#include <raylib.h>
#include <string.h>

static const int EMPTY_CELL = 0;
static const int PLAYER_CELL = 1;
static const int OPP_CELL = 2;

typedef struct {
	int positions[9];
	int x_start;
	int y_start;
	int size; 
} Game; 

void T_InitGame(Game* game);
void T_FreeGame(Game* game);

void T_DrawGame(Game* game);

// Returns the cell at given position, or -1 if no cell 
int T_GetCellPosition(Game* game, int xpos, int ypos);

#endif