#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include "hex.h"

#define HEX_SIZE 100

void DrawHex(HexPoint center, int radius, Color color);

int main(void)
{
    srand(time(NULL));
    const int screenWidth = 1600;
    const int screenHeight = 900;
    InitWindow(screenWidth, screenHeight, "Hex-Grid-Raylib");
    Camera2D camera = {0};
    camera.target = (Vector2){-200, -200};
    camera.offset = (Vector2){0, 0};
    camera.rotation = 0.0f;
    camera.zoom = 1;
    HexLayout HexLayout;
    HexLayout.orientation = FlatHex;
    HexLayout.size = (Vector2){HEX_SIZE, HEX_SIZE};
    HexLayout.origin = (Vector2){screenWidth / 2 - HEX_SIZE * 2, screenHeight / 2 - HEX_SIZE * 2};
    Hex hex = CreateHex(0, 0, 0);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(camera);
        DrawHex(HexToPixel(HexLayout, HexNeighbour(hex, DOWN_RIGHT)), HEX_SIZE, GREEN);
        DrawHex(HexToPixel(HexLayout, HexNeighbour(hex, UP_RIGHT)), HEX_SIZE, GREEN);
        DrawHex(HexToPixel(HexLayout, HexNeighbour(hex, UP)), HEX_SIZE, GREEN);
        DrawHex(HexToPixel(HexLayout, HexNeighbour(hex, LEFT_UP)), HEX_SIZE, GREEN);
        DrawHex(HexToPixel(HexLayout, HexNeighbour(hex, LEFT)), HEX_SIZE, GREEN);
        DrawHex(HexToPixel(HexLayout, HexNeighbour(hex, DOWN)), HEX_SIZE, GREEN);

        DrawHex(HexToPixel(HexLayout, hex), HEX_SIZE, RED);
        EndMode2D();
        DrawFPS(5, 5);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

void DrawHex(HexPoint center, int radius, Color color)
{
    DrawPolyLines((Vector2){center.x, center.y}, 6, radius, 0, color);
}
