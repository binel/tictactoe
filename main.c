#include <raylib.h>

#include "game.h"

int main(int argc, char* argv[]) {
	const int screen_width = 500;
	const int screen_height = 500;
	Game game;
	T_InitGame(&game);
	game.size = 500;

	InitWindow(screen_width, screen_height, "tic tac toe");
	
	SetTargetFPS(60);
	
	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		
		T_DrawGame(&game);
		
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			Vector2 mouse_pos = GetMousePosition();
			int pos = T_GetCellPosition(&game, mouse_pos.x, mouse_pos.y);
			
			if (pos != -1) {
				if (game.positions[pos] == EMPTY_CELL) {
					game.positions[pos] = PLAYER_CELL;
				} else if (game.positions[pos] == PLAYER_CELL) {
					game.positions[pos] = OPP_CELL;
				} else {
					game.positions[pos] = EMPTY_CELL;
				}
			}
		}
		
		EndDrawing();
	}
	
	T_FreeGame(&game);
	CloseWindow();
}