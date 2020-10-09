#include<iostream>
using namespace std;

class Circle
{
public:

    Circle()
    {
        float x = 0;
        float  y = 0;
        float  radius = 0;
    }
    bool CircleCollision();
private:
    float x, y, radius;
};

class Square
{
public:
    Square()
    {
        float s_x = 0;      // square position 
        float s_y = 0;
        float s_w = 0;     // dimensions
        float s_h = 0;

    }
    bool SquareCollision();
private:
    float s_x, s_y, s_w, s_h;

};

