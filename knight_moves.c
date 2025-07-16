#include <math.h>
#include <stdio.h>

struct Line
{
    double a, b, c;
};

enum Quadrant
{
    TOPRIGHT = 0b00,
    TOPLEFT = 0b01,
    BOTTOMRIGHT = 0b10,
    BOTTOMLEFT = 0b11,
};

double distance_to_point(struct Line line, double x, double y)
{
    return fabs(line.a * x + line.b * y + line.c) / sqrt(pow(line.a, 2) + pow(line.b, 2));
}

struct Line line_from_point(int x, int y, double m)
{
    struct Line line = {0};
    line.a = m;
    line.b = -1;
    line.c = y - m * x;

    return line;
}

enum Quadrant calculate_quadrant(int start_x, int start_y, int end_x, int end_y)
{
    enum Quadrant quadrant = 0;
    if (start_x > end_x)
    {
        quadrant = quadrant & 0b01;
    }
    if (start_y > end_y)
    {
        quadrant = quadrant & 0b10;
    }

    return quadrant;
}

void quadrant_multiply(enum Quadrant quadrant, int *dx, int *dy)
{
    switch (quadrant)
    {
    case TOPLEFT:
        *dx *= -1;
        return;
    case BOTTOMLEFT:
        *dx *= -1;
        *dy *= -1;
        return;
    case BOTTOMRIGHT:
        *dy *= -1;
        return;
    default:
        return;
    }
}

int knight_moves(int start_x, int start_y, int end_x, int end_y)
{
    enum Quadrant quadrant = calculate_quadrant(start_x, start_y, end_x, end_y);
    int x = start_x;
    int y = start_y;

    int rise;
    int run;

    int result = 0;

    while (1)
    {
        // return the result if the knight is within a 1 square boundry from the end
        if (end_x - x == 0 && end_y - y == 0)
        {
            return result;
        }
        else if (end_x - x == 1 && end_y - y == 0 || end_y - y == 1 && end_x - x == 0)
        {
            return result + 3;
        }
        else if (end_x - x == 1 && end_y - y == 1)
        {
            return result + 2;
        }

        // create lines
        rise = 1;
        run = 2;
        quadrant_multiply(quadrant, &run, &rise);
        struct Line line_a = line_from_point(x, y, (double)rise / (double)run);

        rise = 2;
        run = 1;
        quadrant_multiply(quadrant, &run, &rise);
        struct Line line_b = line_from_point(x, y, (double)rise / (double)run);

        double distance_a = distance_to_point(line_a, end_x, end_y);
        double distance_b = distance_to_point(line_b, end_x, end_y);

        int dx;
        int dy;

        // check closest route
        if (distance_a >= distance_b)
        {
            dx = 1;
            dy = 2;
        }
        else
        {
            dx = 2;
            dy = 1;
        }

        quadrant_multiply(quadrant, &dx, &dy);
        x += dx;
        y += dy;

        // increment moves
        result++;
    }
}

int main()
{
    int result;
    result = knight_moves(1, 1, 1, 2);
    printf("%d\n", result);

    result = knight_moves(4, 4, 5, 6);
    printf("%d\n", result);

    result = knight_moves(1, 1, 8, 8);
    printf("%d\n", result);
    return 0;
}
