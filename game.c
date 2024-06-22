#include "game.h"

void T_InitGame(Game* game) {
	memset(game->positions, EMPTY_CELL, sizeof(game->positions));
	game->x_start = 0;
	game->y_start = 0;
	game->size = 0;
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
	for (int column = 0; column < 3; column++) {
		for (int row = 0; row < 3; row++) {
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
}

int T_GetCellPosition(Game* game, int xpos, int ypos) {
	int cell_width = (int)(game->size / 3.0);
	
	int x = game->x_start; 
	int y = game->y_start; 
	int pos = 0;
	for (int column = 0; column < 3; column++) {
		for (int row = 0; row < 3; row++) {
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
