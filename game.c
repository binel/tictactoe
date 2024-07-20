#include "game.h"

#include <stdio.h>
#include <stdlib.h>


void T_InitGame(Game* game) {
	memset(game->positions, EMPTY_CELL, sizeof(game->positions));
	game->x_start = 0;
	game->y_start = 0;
	game->size = 0;
	game->is_won = -1;
	game->win_position = NO_WIN;
	game->turn = PLAYER_CELL;
}

void T_FreeGame(Game* game) {

}

void T_DrawGame(Game* game) {
	int cell_width = (int)(game->size / 3.0);
	int half_cell_width = (int)(cell_width / 2.0);
	int x = game->x_start;
	int y = game->y_start; 
	
	// Draw gridlines 
	for (int i = 0; i < 3; i++) {
		DrawLine(x, y, x + game->size, y, WHITE);	
		y += cell_width;
	}
	
	y = game->y_start; 
	
	for (int i = 0; i < 3; i++) {
		DrawLine(x, y, x, y + game->size, WHITE);	
		x += cell_width;
	}
	
	// draw cells
	x = game->x_start; 
	y = game->y_start; 
	int pos = 0;
	for (int row = 0; row < 3; row++) {
		for (int column = 0; column < 3; column++) {
			if (game->positions[pos] == PLAYER_CELL) {
				DrawLine(x, y, x + cell_width, y + cell_width, WHITE);
				DrawLine(x, y + cell_width, x + cell_width, y, WHITE);
			} else if (game->positions[pos] == OPP_CELL) {
				DrawCircleLines(x + half_cell_width, y + half_cell_width, half_cell_width - 1, WHITE);
			}
			x += cell_width;
			pos++;
		}
		x = game->x_start;
		y += cell_width;
	}
	
	// draw win if any 
	Color color = game->is_won == PLAYER_CELL ? RED : BLUE;
	Vector2 start;
	Vector2 end;
	float thickness = 5.0f;
	switch (game->win_position) {
		case ROW_1: 
			start.x = game->x_start;
			start.y = game->y_start + half_cell_width;
			end.x = game->x_start + game->size;
			end.y = game->y_start + half_cell_width;
			break;
		case ROW_2: 
			start.x = game->x_start;
			start.y = game->y_start + half_cell_width + cell_width;
			end.x = game->x_start + game->size;
			end.y = game->y_start + half_cell_width + cell_width; 		
		case ROW_3: 
			start.x = game->x_start;
			start.y = game->y_start + half_cell_width + cell_width + cell_width;
			end.x = game->x_start + game->size;
			end.y = game->y_start + half_cell_width + cell_width + cell_width; 	
			break;	
		case COLUMN_1: 
			start.x = game->x_start + half_cell_width;
			start.y = game->y_start;
			end.x = game->x_start + half_cell_width;
			end.y = game->y_start + game->size; 
			break;
		case COLUMN_2: 
			start.x = game->x_start + half_cell_width + cell_width;
			start.y = game->y_start;
			end.x = game->x_start + half_cell_width + cell_width;
			end.y = game->y_start + game->size; 
			break;
		case COLUMN_3: 
			start.x = game->x_start + half_cell_width + cell_width + cell_width;
			start.y = game->y_start;
			end.x = game->x_start + half_cell_width + cell_width + cell_width;
			end.y = game->y_start + game->size; 
			break;
		case DIAG_DOWN:
			start.x = game->x_start;
			start.y = game->y_start;
			end.x = game->x_start + game->size;
			end.y = game->y_start + game->size; 
			break; 
		case DIAG_UP:
			start.x = game->x_start;
			start.y = game->y_start + game->size;
			end.x = game->x_start + game->size;
			end.y = game->y_start; 
			break; 
		case NO_WIN:
		default:
			break;
	}
	DrawLineEx(start, end, thickness, color);
}

int T_GetCellPosition(Game* game, int xpos, int ypos) {
	int cell_width = (int)(game->size / 3.0);
	
	int x = game->x_start; 
	int y = game->y_start; 
	int pos = 0;
	for (int row = 0; row < 3; row++) {
		for (int column = 0; column < 3; column++) {
			if (xpos > x && xpos < x + cell_width && ypos > y && ypos < y + cell_width) {
				return pos;
			}
			x += cell_width;
			pos++;
		}
		x = game->x_start;
		y += cell_width;
	}
	
	return -1;
}

static bool IsRowSame(Game* game, int startPos) {
	return game->positions[startPos] != EMPTY_CELL
		&& game->positions[startPos] == game->positions[startPos + 1]
		&& game->positions[startPos + 1] == game->positions[startPos + 2];
}

static bool IsColumnSame(Game* game, int colNum) {
	return game->positions[colNum] != EMPTY_CELL
		&& game->positions[colNum] == game->positions[colNum + 3] 
		&& game->positions[colNum + 3] == game->positions[colNum + 6];
}

void T_CheckGameWon(Game* game) {
	game->is_won = -1;
	game->win_position = NO_WIN;

	// probably a better way to do this 
	// row 1 
	if (IsRowSame(game, 0)) {
		if (game->positions[0] == PLAYER_CELL) {
			game->is_won = PLAYER_CELL;
			game->win_position = ROW_1;
		} else if (game->positions[0] == OPP_CELL) {
			game->is_won = OPP_CELL;
			game->win_position = ROW_1;
		}
	}
	
	// row 2
	else if (IsRowSame(game, 3)) {
		if (game->positions[3] == PLAYER_CELL) {
			game->is_won = PLAYER_CELL;
			game->win_position = ROW_2;
		} else if (game->positions[3] == OPP_CELL) {
			game->is_won = OPP_CELL;
			game->win_position = ROW_2;
		}
	}
	
	// row 3
	else if (IsRowSame(game, 6)) {
		if (game->positions[6] == PLAYER_CELL) {
			game->is_won = PLAYER_CELL;
			game->win_position = ROW_3;
		} else if (game->positions[6] == OPP_CELL) {
			game->is_won = OPP_CELL;
			game->win_position = ROW_3;
		}
	}
	
	// column 1
	else if (IsColumnSame(game, 0)) {
		if (game->positions[0] == PLAYER_CELL) {
			game->is_won = PLAYER_CELL;
			game->win_position = COLUMN_1;
		} else if (game->positions[0] == OPP_CELL) {
			game->is_won = OPP_CELL;
			game->win_position = COLUMN_1;
		}
	}
	
	// column 2
	else if (IsColumnSame(game, 1)) {
		if (game->positions[1] == PLAYER_CELL) {
			game->is_won = PLAYER_CELL;
			game->win_position = COLUMN_2;
		} else if (game->positions[1] == OPP_CELL) {
			game->is_won = OPP_CELL;
			game->win_position = COLUMN_2;
		}
	}		
	
	// column 3
	else if (IsColumnSame(game, 2)) {
		if (game->positions[2] == PLAYER_CELL) {
			game->is_won = PLAYER_CELL;
			game->win_position = COLUMN_3;
		} else if (game->positions[2] == OPP_CELL) {
			game->is_won = OPP_CELL;
			game->win_position = COLUMN_3;
		}
	}
	
	// diagonal down
	else if (game->positions[0] != EMPTY_CELL
		&& game->positions[0] == game->positions[4] 
		&& game->positions[4] == game->positions[8]) {
		if (game->positions[0] == PLAYER_CELL) {
			game->is_won = PLAYER_CELL;
			game->win_position = DIAG_DOWN;
		} else if (game->positions[0] == OPP_CELL) {
			game->is_won = OPP_CELL;
			game->win_position = DIAG_DOWN;
		}			
	}

	// diagonal up
	else if (game->positions[2] != EMPTY_CELL
		&& game->positions[2] == game->positions[4] 
		&& game->positions[4] == game->positions[6]) {
		if (game->positions[2] == PLAYER_CELL) {
			game->is_won = PLAYER_CELL;
			game->win_position = DIAG_UP;
		} else if (game->positions[2] == OPP_CELL) {
			game->is_won = OPP_CELL;
			game->win_position = DIAG_UP;
		}			
	}
}

static int GetOpenCountPositions(Game* game) {
	int open_count = 0;
	for (int i = 0; i < 9; i++) {
		if (game->positions[i] == EMPTY_CELL) {
			open_count++;
		}
	}
	
	return open_count;	
}

void T_MakeRandomMove(Game* game) {
	int open_count = GetOpenCountPositions(game);
	
	int move = rand() % open_count;
	
	for(int i = 0; i < 9; i++) {
		if (game->positions[i] == EMPTY_CELL) { 
			if (move == 0) {
				game->positions[i] = OPP_CELL;
				return;
			} else {
				move--;
			}
		} 
	}
}
