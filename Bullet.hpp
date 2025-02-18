#ifndef BULLET_H
#define BULLET_H

#include "Entity.hpp"

class Bullet : public Entity
{
private:
    float m_speed = 500.0;
    double direction;
public: 
    Bullet(Vector2 position, float height, float width, std::string path, double direction);
    void Update(float deltaTime) override;
    void Draw() override;
}
;
#endif