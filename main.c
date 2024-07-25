#include <raylib.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "game.h"

const bool SCREEN_RECORD = false;

int main(int argc, char* argv[]) {
	srand(time(NULL));

	int screen_width = 500;
	int screen_height = 500;
	Game game;
	T_InitGame(&game);
	game.size = screen_width;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screen_width, screen_height, "tic tac toe");
	
	SetTargetFPS(30);
	int frameCounter = 0;
	
	while(!WindowShouldClose()) {
	
		if(IsWindowResized()) {
			screen_width = GetScreenWidth();
			screen_height = GetScreenHeight();
			
			game.size = screen_height > screen_width ? screen_width : screen_height;
		}
	
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

		T_DrawGame(&game);
	
		if (SCREEN_RECORD) {
			char filename[32];
			snprintf(filename, sizeof(filename), "frame%04d.png", frameCounter++);
			TakeScreenshot(filename);			
		}

		BeginDrawing();
		ClearBackground(BLACK);
		
		EndDrawing();
		

	}
	
	T_FreeGame(&game);
	CloseWindow();
}