#include "raylib.h"

const int CELLS_X = 10;
const int CELLS_Y = 10;

void fillWithZeros (int (&cell)[10][10])
{
    for (int i = 0; i < CELLS_X; i++) {for (int j = 0; j < CELLS_Y; j++) {cell[i][j] = 0;}}
}

void update (int (&cell)[10][10])
{
    int updated[10][10];
    for (int i = 0; i < CELLS_X; i++) {for (int j = 0; j < CELLS_Y; j++) {updated[i][j] = cell[i][j];}}
    for (int i = 1; i < CELLS_X-1; i++) {for (int j = 1; j < CELLS_Y-1; j++) {
        int neighbours[4] = {cell[i-1][j],cell[i+1][j],cell[i][j-1],cell[i][j+1]};
        if (neighbours[0]+neighbours[1]+neighbours[2]+neighbours[3] < 1) {updated[i][j] = 1;}
        if (neighbours[0]+neighbours[1]+neighbours[2]+neighbours[3] > 2) {updated[i][j] = 0;}
    }}
    for (int i = 0; i < CELLS_X; i++) {for (int j = 0; j < CELLS_Y; j++) {cell[i][j] = updated[i][j];}}
}

int main ()
{
    int cell[CELLS_X][CELLS_Y];
    fillWithZeros(cell);

	InitWindow(704, 704, "Cellular");
	
	while (!WindowShouldClose())
	{
		if (IsKeyDown(KEY_SPACE)) update(cell);
        BeginDrawing();

		ClearBackground(BLACK);
		for (int i = 0; i < CELLS_X; i++) {for (int j = 0; j < CELLS_Y; j++) {
        if (cell[i][j] == 0) {DrawText(".", 64*i+64, 64*j+64, 24, WHITE);}
        else if (cell[i][j] == 1) {DrawText("O", 64*i+64, 64*j+64, 24, WHITE);}
        }}
		
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
