#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"
#include <string>


class Entity
{
protected:
    Vector2 position;
    Rectangle frameRec;
    Texture2D texture;
    bool active;
    float height;
    float width;
    
public:
    Entity(Vector2 position, float height, float width, std::string path);
    virtual ~Entity();
    
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;

    void Deactivate();
    Vector2 getPosition() const;
    Rectangle getFrameRec() const;
    void setPosition(Vector2 pos);
    bool isActive() const;

    bool checkColision(Rectangle& outroRect) const;

}
;

#endif