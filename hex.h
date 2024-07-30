#ifndef HEX_H
#define HEX_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <raylib.h>

// TODO: this is not really a good way to do this
typedef enum HexDirection
{
    DOWN_RIGHT,
    UP_RIGHT,
    UP,
    LEFT_UP,
    LEFT,
    DOWN,

} HexDirection;

typedef struct Hex
{
    int q;
    int r;
    int s;
} Hex;

typedef struct Orientation
{
    float f0;
    float f1;
    float f2;
    float f3;
    float b0;
    float b1;
    float b2;
    float b3;
    float start_angle;
} Orientation;

typedef struct HexLayout
{
    Orientation orientation;
    Vector2 size;
    Vector2 origin;
} HexLayout;

typedef struct HexPoint
{
    float x;
    float y;
} HexPoint;

extern const Orientation FlatHex;

extern const Orientation PointyHex;

Hex CreateHex(int q, int r, int s);
bool IsEquals(Hex a, Hex b);
Hex HexAdd(Hex a, Hex b);
Hex HexSubtract(Hex a, Hex b);
Hex HexMultiply(Hex a, int k);
int HexLength(Hex hex);
int HexDistance(Hex a, Hex b);
Hex HexGetDirection(int direction);
Hex HexNeighbour(Hex hex, int direction);
HexPoint HexToPixel(HexLayout layout, Hex h);
Hex PixelToHex(HexLayout layout, HexPoint p);
HexPoint HexCornerOffset(HexLayout layout, int corner);
HexPoint *PolygonCorners(HexLayout layout, Hex h);
Hex *HexDirections();
#endif