#include "Bullet.hpp"


Bullet::Bullet(Vector2 position, float height, float width, std::string path, double direction) 
: Entity(position, height, width, path), direction(direction)
{
}

void Bullet::Draw()
{
    DrawRectangleV(position, {20, 20}, WHITE);
}


void Bullet::Update(float deltaTime)
{
    frameRec.x += m_speed * direction * deltaTime;
    frameRec.y += m_speed * direction * deltaTime;
}
