#ifndef t_game_h
#define t_game_h

#include <raylib.h>
#include <string.h>

static const int EMPTY_CELL = 0;
static const int PLAYER_CELL = 1;
static const int OPP_CELL = 2;

enum WinPositions {
	NO_WIN,
	ROW_1,
	ROW_2,
	ROW_3,
	COLUMN_1,
	COLUMN_2,
	COLUMN_3,
	DIAG_DOWN,
	DIAG_UP,
};


typedef struct {
	int positions[9];
	int x_start;
	int y_start;
	int size; 
	int is_won;
	enum WinPositions win_position;
	int turn;
} Game; 


void T_InitGame(Game* game);
void T_FreeGame(Game* game);

void T_DrawGame(Game* game);

// Returns the cell at given position, or -1 if no cell 
int T_GetCellPosition(Game* game, int xpos, int ypos);

// Checks if the game is won. Updates game.is_won with either -1 (no win),
// PLAYER_CELL if the player won, OPP_CELL if the opponent won 
void T_CheckGameWon(Game* game);

void T_MakeRandomMove(Game* game);

#endif