#pragma once
#include "LevelManager.h"

struct Circle {

    float xpos = 0;
    float ypos = 0;
    float radius = 0;

    Circle(float xpos, float ypos, float radius);
    Circle();
};

struct Square {
    float squarePosx   = 0;      // square position 
    float squarePosy   = 0;
    float squareWidth  = 0;     // dimensions
    float squareHeight = 0;

    Square(float xpos, float ypos, float width, float height);
    Square();
};

class CollisionManager
{
public:
    CollisionManager();
    ~CollisionManager();
    void init(LevelManager& levelManager);
    bool check_circle_collision(Circle circle1, Circle circle2);
    bool check_square_collision(Square square1 ,Square square2);
    bool is_square_on_restricted_tile(const glm::vec2& center, const glm::vec2& dims);
    bool is_point_on_restricted_tile(const glm::vec2& center);


private:
    LevelManager* m_levelManager = nullptr;
};

