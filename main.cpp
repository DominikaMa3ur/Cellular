#include "raylib.h"
#include <climits>
#include <vector>

const int EDGE_NEIGHBOUR = INT_MAX;

int CELLS_X = 128;
int CELLS_Y = 128;

Color COLORS[2] = {Color{146,236,68,255},Color{182,252,56,255}};

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

NEIGHBOURS4 returnNeighbours(std::vector<std::vector<int>> &cell, int x, int y) {
    NEIGHBOURS4 returned;
    if (y <= 0) returned.TOP = EDGE_NEIGHBOUR;
    else returned.TOP = cell[x][y-1];
    if (y >= CELLS_Y-1) returned.BOTTOM = EDGE_NEIGHBOUR;
    else returned.BOTTOM = cell[x][y+1];
    if (x <= 0) returned.LEFT = EDGE_NEIGHBOUR;
    else returned.LEFT = cell[x-1][y];
    if (x >= CELLS_X-1) returned.RIGHT = EDGE_NEIGHBOUR;
    else returned.RIGHT = cell[x+1][y];
    return returned;
}

void update(std::vector<std::vector<int>> &cell)
{
    std::vector<std::vector<int>> updated(CELLS_X, std::vector<int>(CELLS_Y,0));
    for (int i = 0; i < CELLS_X; i++) {for (int j = 0; j < CELLS_Y; j++) {updated[i][j] = cell[i][j];}}
    for (int i = 0; i < CELLS_X; i++) {for (int j = 0; j < CELLS_Y; j++) {
        if (countNeighbours(returnNeighbours(cell,i,j),1) < 1) {updated[i][j] = 1;}
        if (countNeighbours(returnNeighbours(cell,i,j),1) > 3) {updated[i][j] = 0;}
    }}
    for (int i = 0; i < CELLS_X; i++) {for (int j = 0; j < CELLS_Y; j++) {cell[i][j] = updated[i][j];}}
}

int main ()
{
    std::vector<std::vector<int>> cell(CELLS_X, std::vector<int>(CELLS_Y,0));

    const float updateTime = 1.25;
    float sinceUpdate = 0;
    bool updateKeyReleased = true;

	InitWindow(640, 640, "Cellular");
    int square = 640/std::max(CELLS_X,CELLS_Y);
	
	while (!WindowShouldClose())
	{
        float delta = GetFrameTime();
        sinceUpdate += delta;
        while (sinceUpdate >= updateTime) {update(cell); sinceUpdate -= updateTime;}
        if (IsKeyDown(KEY_SPACE) && updateKeyReleased) {update(cell); updateKeyReleased = false;}
        else if (!IsKeyDown(KEY_SPACE)) {updateKeyReleased = true;}
        BeginDrawing();

		ClearBackground(BLACK);
		for (int i = 0; i < CELLS_X; i++) {for (int j = 0; j < CELLS_Y; j++) {
        if (cell[i][j] == 0) {DrawRectangle(square*i, square*j, square, square, COLORS[0]);}
        else if (cell[i][j] == 1) {DrawRectangle(square*i, square*j, square, square, COLORS[1]);}
        }}
		
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
