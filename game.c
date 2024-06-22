#include "game.h"

void T_InitGame(Game* game) {
	memset(game->positions, EMPTY_CELL, sizeof(game->positions));
}

void T_FreeGame(Game* game) {

}

void T_DrawGame(int x_start, int y_start, int size, Game game) {
	int cell_width = (int)(size / 3.0);
	int half_cell_width = (int)(cell_width / 2.0);
	int x = x_start;
	int y = y_start; 
	
	// Draw gridlines 
	for (int i = 0; i < 3; i++) {
		DrawLine(x, y, x + size, y, WHITE);	
		y += cell_width;
	}
	
	y = y_start; 
	
	for (int i = 0; i < 3; i++) {
		DrawLine(x, y, x, y + size, WHITE);	
		x += cell_width;
	}
	
	// draw cells
	x = x_start; 
	y = y_start; 
	int pos = 0;
	for (int column = 0; column < 3; column++) {
		for (int row = 0; row < 3; row++) {
			if (game.positions[pos] == PLAYER_CELL) {
				DrawLine(x, y, x + cell_width, y + cell_width, WHITE);
				DrawLine(x, y + cell_width, x + cell_width, y, WHITE);
			} else if (game.positions[pos] == OPP_CELL) {
				DrawCircleLines(x + half_cell_width, y + half_cell_width, half_cell_width, WHITE);
			}
			x += cell_width;
			pos++;
		}
		x = x_start;
		y += cell_width;
	}
	
}

