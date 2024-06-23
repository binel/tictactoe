#include <raylib.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "game.h"

int main(int argc, char* argv[]) {
	srand(time(NULL));

	const int screen_width = 500;
	const int screen_height = 500;
	Game game;
	T_InitGame(&game);
	game.size = 500;

	InitWindow(screen_width, screen_height, "tic tac toe");
	
	SetTargetFPS(60);
	
	while(!WindowShouldClose()) {
	
		if (game.is_won == -1 && game.turn == OPP_CELL) {
			T_MakeRandomMove(&game);
			game.turn = PLAYER_CELL;
		}
	
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			Vector2 mouse_pos = GetMousePosition();
			int pos = T_GetCellPosition(&game, mouse_pos.x, mouse_pos.y);
			if (pos != -1) {
				if (game.positions[pos] == EMPTY_CELL) {
					game.positions[pos] = PLAYER_CELL;
					game.turn = OPP_CELL;
				} 
			}
		}
		
		T_CheckGameWon(&game);	

		BeginDrawing();
		ClearBackground(BLACK);
		
		T_DrawGame(&game);
		
		EndDrawing();
	}
	
	T_FreeGame(&game);
	CloseWindow();
}