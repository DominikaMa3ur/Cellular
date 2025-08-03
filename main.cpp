#include "raylib.h"

struct NEIGHBOURS4 {
    int TOP;
    int LEFT;
    int RIGHT;
    int BOTTOM;
};

int countNeighbours(NEIGHBOURS4 neighbours, int value) {
    int count = 0;
    if (neighbours.TOP == value) {count++;}
    if (neighbours.LEFT == value) {count++;}
    if (neighbours.RIGHT == value) {count++;}
    if (neighbours.BOTTOM == value) {count++;}
    return count;
}

NEIGHBOURS4 returnNeighbours(int (&cell)[10][10], int x, int y) {
    NEIGHBOURS4 returned;
    returned.TOP = cell[x][y-1];
    returned.BOTTOM = cell[x][y+1];
    returned.LEFT = cell[x-1][y];
    returned.RIGHT = cell[x+1][y];
    return returned;
}

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
        if (countNeighbours(returnNeighbours(cell,i,j),1) < 1) {updated[i][j] = 1;}
        if (countNeighbours(returnNeighbours(cell,i,j),1) > 3) {updated[i][j] = 0;}
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
