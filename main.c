#include <raylib.h>

#include "game.h"

int main(int argc, char* argv[]) {
	const int screen_width = 500;
	const int screen_height = 500;
	Game game;
	T_InitGame(&game);

	InitWindow(screen_width, screen_height, "tic tac toe");
	
	SetTargetFPS(60);
	
	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		
		T_DrawGame(0, 0, 500, game);
		
		EndDrawing();
	}
	
	T_FreeGame(&game);
	CloseWindow();
}