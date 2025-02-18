#include "Bullet.hpp"
#include <cmath>
#include <iostream>

Bullet::Bullet(Vector2 position, float height, float width, std::string path, double direction) 
: Entity(position, height, width, path), direction(direction)
{
}

void Bullet::Draw()
{
    DrawRectangleV({frameRec.x, frameRec.y}, {width, height}, PURPLE);
    // Rectangle source = { 0, 0, 700, 700};
    // Vector2 origin = { frameRec.width / 2, frameRec.height / 2 }; 

    // DrawTexturePro(texture, source, frameRec, origin, 0.0f, WHITE);
    // // DrawTextureEx(texture, origin, 0.0f, 1.0f, WHITE);

}




void Bullet::Update(float deltaTime)
{
    double rad = direction * DEG2RAD;

    frameRec.x += m_speed * cos(rad) * deltaTime;
    frameRec.y += m_speed * sin(rad) * deltaTime;

    if (frameRec.x < 0 || frameRec.x > GetScreenWidth() || frameRec.y < 0 || frameRec.y > GetScreenHeight()) {
        active = false;  
    }
}
