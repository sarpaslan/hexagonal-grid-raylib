#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include "hex.h"

#define HEX_SIZE 100

void DrawHex(HexPoint center, int radius, Color color);
Color RandomColor();

int main(void)
{
    srand(time(NULL));
    const int screenWidth = 900;
    const int screenHeight = 900;
    InitWindow(screenWidth, screenHeight, "Hex-Grid-Raylib");
    Camera2D camera = {0};
    camera.target = (Vector2){-200, -200};
    camera.offset = (Vector2){-HEX_SIZE, 0};
    camera.rotation = 0.0f;
    camera.zoom = 0.6;
    HexLayout layout;
    layout.orientation = FlatHex;
    layout.size = (Vector2){HEX_SIZE, HEX_SIZE};
    layout.origin = (Vector2){0, 0};

    Color *colors = (Color *)malloc(20 * sizeof(Color));
    // because it looks cool
    for (int i = 0; i < 20; i++)
    {
        colors[i] = RandomColor();
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(camera);
        // Todo : fix creation logic
        for (int q = 0; q < 20; q++)
        {
            for (int r = -5; r <= 10; r++)
            {
                Hex h = CreateHex(q, r, -q - r);
                HexPoint *corners = PolygonCorners(layout, h);
                Color random = colors[q];
                for (int i = 0; i < 6; i++)
                {
                    HexPoint p1 = corners[i];
                    HexPoint p2 = corners[(i + 1) % 6];
                    DrawLine(p1.x, p1.y, p2.x, p2.y, random);
                }
                char *text = TextFormat("q:%d\n\nr:%d\n\ns:%d", h.q, h.r, h.s);
                HexPoint point = HexToPixel(layout, h);
                DrawText(text, point.x, point.y, 25, WHITE);
                free(corners);
            }
        }
        EndMode2D();
        DrawFPS(5, 5);
        EndDrawing();
    }
    free(colors);
    CloseWindow();
    return 0;
}

Color RandomColor()
{
    return (Color){rand() % 255, rand() % 255, rand() % 255, 255};
}

void DrawHex(HexPoint center, int radius, Color color)
{
    DrawPolyLines((Vector2){center.x, center.y}, 6, radius, 0, color);
}
