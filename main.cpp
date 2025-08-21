#include "raylib.h"
#include <climits>
#include <vector>
#include <fstream>
#include <sstream>

const int EDGE_NEIGHBOUR = INT_MAX;

int CELLS_X = 128;
int CELLS_Y = 128;

Color COLORS[2] = {Color{128,128,128,255},Color{192,192,192,255}};

struct NEIGHBOURS4 {
    int TOP;
    int LEFT;
    int RIGHT;
    int BOTTOM;
};

struct RULE2 {int a; int b;};

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

int returnNeighbours4Num(NEIGHBOURS4 n, int value=1) {
    int num = 0;
    if (n.TOP == value) {num += 1;}
    if (n.RIGHT == value) {num += 2;}
    if (n.BOTTOM == value) {num += 4;}
    if (n.LEFT == value) {num += 8;}
    return num;
}

void update(std::vector<std::vector<int>> &cell, std::vector<RULE2> rules)
{
    std::vector<std::vector<int>> updated(CELLS_X, std::vector<int>(CELLS_Y,0));
    for (int i = 0; i < CELLS_X; i++) {for (int j = 0; j < CELLS_Y; j++) {updated[i][j] = cell[i][j];}}
    for (int i = 0; i < CELLS_X; i++) {for (int j = 0; j < CELLS_Y; j++) {
        for(std::vector<RULE2>::iterator it = rules.begin(); it != rules.end(); it++)
            {if (returnNeighbours4Num(returnNeighbours(cell,i,j)) == (*it).a) {updated[i][j] = (*it).b;}}
    }}
    for (int i = 0; i < CELLS_X; i++) {for (int j = 0; j < CELLS_Y; j++) {cell[i][j] = updated[i][j];}}
}

int main ()
{
    std::vector<std::vector<int>> cell(CELLS_X, std::vector<int>(CELLS_Y,0));
    std::vector<RULE2> rules;
    const float updateTime = 1.25;
    float speed = 0.75;
    float sinceUpdate = 0;
    bool updateKeyReleased = true;
    bool mouseReleased = true;
    bool rulesFound = true;
    
    Rectangle stopButton{0,640,160,32};
    Rectangle startButton{160,640,160,32};
    Rectangle speedButton{320,640,160,32};
    Rectangle restartButton{480,640,160,32};

	InitWindow(640, 672, "Cellular");
    int square = 640/std::max(CELLS_X,CELLS_Y);
    std::ifstream file("rules.txt");
    std::string line;
    if (file.is_open()) {
        while (std::getline(file,line)) {
            std::stringstream stream(line);
            RULE2 i; stream >> i.a >> i.b;
            rules.push_back(i);
        }
    }
    else {rulesFound = false;}
    file.close();

	while (!WindowShouldClose())
	{
        float delta = GetFrameTime();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mouseReleased) {
            if (CheckCollisionPointRec(GetMousePosition(), startButton))
            {speed = 1.0; mouseReleased = false;}
            else if (CheckCollisionPointRec(GetMousePosition(), stopButton))
            {speed = 0.0; mouseReleased = false;}
            else if (CheckCollisionPointRec(GetMousePosition(), speedButton))
            {speed = 2.0; mouseReleased = false;}
            else if (CheckCollisionPointRec(GetMousePosition(), restartButton))
            {speed = 1.0; mouseReleased = false;
            cell = std::vector<std::vector<int>>(CELLS_X, std::vector<int>(CELLS_Y,0));}
        }
        if (not IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {mouseReleased = true;}
        sinceUpdate += delta*speed;
        while (sinceUpdate >= updateTime) {update(cell, rules); sinceUpdate -= updateTime;}
        if (IsKeyDown(KEY_SPACE) && updateKeyReleased) {update(cell, rules); updateKeyReleased = false;}
        else if (!IsKeyDown(KEY_SPACE)) {updateKeyReleased = true;}
        BeginDrawing();

		ClearBackground(BLACK);
		for (int i = 0; i < CELLS_X; i++) {for (int j = 0; j < CELLS_Y; j++) {
        if (cell[i][j] == 0) {DrawRectangle(square*i, square*j, square, square, COLORS[0]);}
        else if (cell[i][j] == 1) {DrawRectangle(square*i, square*j, square, square, COLORS[1]);}}}
        DrawRectangle(stopButton.x,startButton.y,startButton.width,startButton.height,WHITE);
        DrawRectangle(startButton.x,restartButton.y,restartButton.width,restartButton.height,LIGHTGRAY);
        DrawRectangle(speedButton.x,startButton.y,startButton.width,startButton.height,GRAY);
        DrawRectangle(restartButton.x,restartButton.y,restartButton.width,restartButton.height,BLACK);
		if (!rulesFound) {DrawText("[!] Rules not found! make sure the file is named rules.txt", 16, 16, 20, BLACK);}
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
