#include "hex.h"
//  References | Credits
//  https://www.redblobgames.com/grids/hexagons

Hex CreateHex(int q, int r, int s)
{
    Hex hex;
    hex.q = q;
    hex.r = r;
    hex.s = s;
    return hex;
}
bool IsEquals(Hex a, Hex b)
{
    return a.q == b.q && a.r == b.r && a.s == b.s;
}

Hex HexAdd(Hex a, Hex b)
{
    return CreateHex(a.q + b.q, a.r + b.r, a.s + b.s);
}
Hex HexSubtract(Hex a, Hex b)
{
    return CreateHex(a.q - b.q, a.r - b.r, a.s - b.s);
}
Hex HexMultiply(Hex a, int k)
{
    return CreateHex(a.q * k, a.r * k, a.s * k);
}
int HexLength(Hex hex)
{
    return (abs(hex.q) + abs(hex.r) + abs(hex.s)) / 2;
}
int HexDistance(Hex a, Hex b)
{
    return HexLength(HexSubtract(a, b));
}

Hex HexGetDirection(int direction)
{
    if (direction < 0 || direction > 5)
    {
        printf("Invalid direction\n");
        return CreateHex(0, 0, 0);
    }
    Hex *directions = HexDirections();
    return directions[direction];
}

Hex HexNeighbour(Hex hex, int direction)
{
    return HexAdd(hex, HexGetDirection(direction));
}

HexPoint HexToPixel(HexLayout layout, Hex h)
{
    Orientation M = layout.orientation;
    float x = (M.f0 * h.q + M.f1 * h.r) * layout.size.x;
    float y = (M.f2 * h.q + M.f3 * h.r) * layout.size.y;
    return (HexPoint){x + layout.origin.x, y + layout.origin.y};
}

Hex PixelToHex(HexLayout layout, HexPoint p)
{
    Orientation M = layout.orientation;
    HexPoint pt = (HexPoint){(p.x - layout.origin.x) / layout.size.x, (p.y - layout.origin.y) / layout.size.y};
    float q = M.b0 * pt.x + M.b1 * pt.y;
    float r = M.b2 * pt.x + M.b3 * pt.y;
    return CreateHex(q, r, -q - r);
}

HexPoint HexCornerOffset(HexLayout layout, int corner)
{
    Orientation M = layout.orientation;
    float angle = 2.0 * PI * (M.start_angle - corner) / 6;
    return (HexPoint){layout.size.x * cos(angle), layout.size.y * sin(angle)};
}

HexPoint *PolygonCorners(HexLayout layout, Hex h)
{
    HexPoint *corners = (HexPoint *)malloc(6 * sizeof(HexPoint));
    if (corners == NULL)
    {
        return NULL;
    }
    HexPoint center = HexToPixel(layout, h);
    for (int i = 0; i < 6; i++)
    {
        HexPoint offset = HexCornerOffset(layout, i);
        corners[i] = (HexPoint){center.x + offset.x, center.y + offset.y};
    }
    return corners;
}

Hex *HexDirections()
{
    static Hex directions[6];
    directions[0] = CreateHex(1, 0, -1);
    directions[1] = CreateHex(1, -1, 0);
    directions[2] = CreateHex(0, -1, 1);
    directions[3] = CreateHex(-1, 0, 1);
    directions[4] = CreateHex(-1, 1, 0);
    directions[5] = CreateHex(0, 1, -1);
    return directions;
}

const Orientation FlatHex = {3.0 / 2.0, 0.0, sqrt(3.0) / 2.0, sqrt(3.0), 2.0 / 3.0, 0.0, -1.0 / 3.0, sqrt(3.0) / 3.0, 0.0};

const Orientation PointyHex = {sqrt(3.0), sqrt(3.0) / 2.0, 0.0, 3.0 / 2.0, sqrt(3.0) / 3.0, -1.0 / 3.0, 0.0, 2.0 / 3.0, 0.5};