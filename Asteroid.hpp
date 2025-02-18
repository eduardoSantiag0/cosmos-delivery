#ifndef ASTEROID_H
#define ASTEROID_H

#include "Entity.hpp"
#include <cmath>
#include <string>

class Asteroid : public Entity {
public:
    Asteroid(Vector2 position, float height, float width, std::string path, float speed, float rotationSpeed);
    void Update(float deltaTime) override;
    void Draw() override;
    
private:
    float speed;          
    float rotation;        
    float rotationSpeed;   
    float directionAngle;  
};


#endif
