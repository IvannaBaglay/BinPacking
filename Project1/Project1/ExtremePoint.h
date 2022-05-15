#pragma once

struct ExtremePoint
{
    ExtremePoint(int x, int y, int z)
        : X_Coord(x), Y_Coord(y), Z_Coord(z) {}

    bool operator==(const ExtremePoint& point)
    {
        return X_Coord == point.X_Coord && Y_Coord == point.Y_Coord && Z_Coord == point.Z_Coord;
    }

    int X_Coord;
    int Y_Coord;
    int Z_Coord;
};

enum class Projections 
{
    Y_x = 0,
    Y_z = 1,
    X_y = 2,
    X_z = 3,
    Z_x = 4,
    Z_y = 5
};