#include<iostream>
#include "GameCollision.h"
using namespace std;



Circle circle1;
Circle circle2;
Square square1;
Square square2;
bool Circle::CircleCollision()                                 //- Circle collision
{

    float distance_x = circle1.x - circle2.x;
    float distance_y = circle1.y - circle2.y;

    float radii_sum = circle1.radius + circle2.radius;

    if ((distance_x * distance_x) + (distance_y * distance_y) <= (radii_sum * radii_sum))
    {
        return true;
    }
    return false;

};

bool Square::SquareCollision()
{
    if (square1.s_x + square1.s_w >= square2.s_x                    //  right edge past square2 left
        && square1.s_x <= square2.s_x + square2.s_w &&          // square1 left edge past square2 right
        square1.s_y + square1.s_h >= square2.s_y &&             // square1 top edge past square2 bottom
        square1.s_y <= square2.s_y + square2.s_h)              // square1 bottom edge past square2 top)
    {
        return true;
    }
    return false;

}