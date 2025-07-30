#include "raylib.h"

int main ()
{
    const int CELLS_X = 10;
    const int CELLS_Y = 10;

    int cell[CELLS_X][CELLS_Y];
    for (int i = 0; i < CELLS_X; i++) {for (int j = 0; j < CELLS_Y; j++) {cell[i][j] = 1;}}

	InitWindow(704, 704, "Cellular");
	
	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(BLACK);
		for (int i = 0; i < CELLS_X; i++) {for (int j = 0; j < CELLS_Y; j++) {
        DrawText("1", 64*i+64, 64*j+64, 24, WHITE);
        }}
		
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
