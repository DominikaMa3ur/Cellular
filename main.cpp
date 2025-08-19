#include "raylib.h"
#include <climits>

const int EDGE_NEIGHBOUR = INT_MAX;

const int CELLS_X = 20;
const int CELLS_Y = 20;

Color COLORS[2] = {Color{0,0,0,255},Color{255,255,255,255}};

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

NEIGHBOURS4 returnNeighbours(int (&cell)[CELLS_X][CELLS_Y], int x, int y) {
    NEIGHBOURS4 returned;
    if (y == 0) returned.TOP = EDGE_NEIGHBOUR;
    else returned.TOP = cell[x][y-1];
    if (y == CELLS_Y-1) returned.BOTTOM = EDGE_NEIGHBOUR;
    else returned.BOTTOM = cell[x][y+1];
    if (x == 0) returned.LEFT = EDGE_NEIGHBOUR;
    else returned.LEFT = cell[x-1][y];
    if (x == CELLS_X-1) returned.RIGHT = EDGE_NEIGHBOUR;
    else returned.RIGHT = cell[x+1][y];
    return returned;
}

void fillWithZeros (int (&cell)[CELLS_X][CELLS_Y])
{
    for (int i = 0; i < CELLS_X; i++) {for (int j = 0; j < CELLS_Y; j++) {cell[i][j] = 0;}}
}

void update (int (&cell)[CELLS_X][CELLS_Y])
{
    int updated[CELLS_X][CELLS_Y];
    for (int i = 0; i < CELLS_X; i++) {for (int j = 0; j < CELLS_Y; j++) {updated[i][j] = cell[i][j];}}
    for (int i = 0; i < CELLS_X; i++) {for (int j = 0; j < CELLS_Y; j++) {
        int neighbours[4] = {cell[i-1][j],cell[i+1][j],cell[i][j-1],cell[i][j+1]};
        if (countNeighbours(returnNeighbours(cell,i,j),1) < 2) {updated[i][j] = 1;}
        if (countNeighbours(returnNeighbours(cell,i,j),1) > 3) {updated[i][j] = 0;}
    }}
    for (int i = 0; i < CELLS_X; i++) {for (int j = 0; j < CELLS_Y; j++) {cell[i][j] = updated[i][j];}}
}

int main ()
{
    int cell[CELLS_X][CELLS_Y];
    fillWithZeros(cell);
    const int updateTime = 1.25;
    float sinceUpdate = 0;

	InitWindow(704, 704, "Cellular");
	
	while (!WindowShouldClose())
	{
        float delta = GetFrameTime();
        sinceUpdate += delta;
        while (sinceUpdate >= updateTime) {update(cell); sinceUpdate -= updateTime;}
        //if (IsKeyDown(KEY_SPACE)) update(cell); // to be improved
        BeginDrawing();

		ClearBackground(BLACK);
		for (int i = 0; i < CELLS_X; i++) {for (int j = 0; j < CELLS_Y; j++) {
        if (cell[i][j] == 0) {DrawRectangle(32*i+32, 32*j+32, 32, 32, COLORS[0]);}
        else if (cell[i][j] == 1) {DrawRectangle(32*i+32, 32*j+32, 32, 32, COLORS[1]);}
        }}
		
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
