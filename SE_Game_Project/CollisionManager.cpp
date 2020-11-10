#include "CollisionManager.h"



 Circle::Circle(float xpos, float ypos, float radius)
{
     this->xpos   = xpos;
     this->ypos =  ypos;
     this->radius =  radius;
};

 Circle::Circle()
 {
     this->xpos = 0.0f;
     this->ypos = 0.0f;
     this->radius = 0.0f;
 };

 Square::Square(float xpos, float ypos, float width, float height)
{
     squarePosx =  xpos;
     squarePosy =  ypos;
     squareWidth = width;
     squareHeight = height;
};

 Square::Square()
 {
     squarePosx = 0.0f;
     squarePosy = 0.0f;
     squareWidth = 0.0f;
     squareHeight = 0.0f;
 };

 CollisionManager::CollisionManager(LevelManager& levelManager)
 {
     m_levelManager = &levelManager;
 }

 bool CollisionManager::check_circle_collision(Circle circle1, Circle circle2)                                 //- Circle collision
{
    float distance_x = circle1.xpos - circle2.xpos;
    float distance_y = circle1.ypos - circle2.ypos;

    float radii_sum = circle1.radius + circle2.radius;

    if ((distance_x * distance_x) + (distance_y * distance_y) <= (radii_sum * radii_sum))
    {
        return true;
    }
    return false;

};

bool CollisionManager::check_square_collision(Square square1, Square square2)         // Square Collision
{
    if (square1.squarePosx + square1.squareWidth >= square2.squarePosx                    //  right edge past square2 left
        && square1.squarePosx <= square2.squarePosx + square2.squareWidth &&          // square1 left edge past square2 right
        square1.squarePosy + square1.squareHeight >= square2.squarePosy &&             // square1 top edge past square2 bottom
        square1.squarePosy <= square2.squarePosy + square2.squareHeight)              // square1 bottom edge past square2 top
    {
        return true;
    }
    return false;

}

bool CollisionManager::is_square_on_restricted_tile(const glm::vec2& center, const glm::vec2& dims)
{
    glm::vec2 tl(center.x - dims.x, center.y + dims.y);
	glm::vec2 tr = center + dims;
	glm::vec2 bl = center - dims;
	glm::vec2 br(center.x + dims.x, center.y - dims.y);
    if (m_levelManager->is_tile_restricted(tl)) { return true; }
	if (m_levelManager->is_tile_restricted(tr)) { return true; }
	if (m_levelManager->is_tile_restricted(bl)) { return true; }
	if (m_levelManager->is_tile_restricted(br)) { return true; }
    return false;
}

