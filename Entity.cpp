#include "Entity.hpp"
#include <iostream>

Entity::Entity(Vector2 position, float height, float width, std::string path) 
: position(position), active(true), width(width), height(height)
{
    frameRec = { position.x, position.y, height, width};
    texture = LoadTexture(path.c_str());
}


Entity::~Entity()
{
    UnloadTexture(texture);
}

bool Entity::checkColision(Rectangle& outroRect) const
{
    return CheckCollisionRecs(frameRec, outroRect);
}


bool Entity::isActive() const { return active; }

Vector2 Entity::getPosition() const {return position; }

void Entity::setPosition (Vector2 pos) { position = pos; }

void Entity::Deactivate() { active = false; }

Rectangle Entity::getFrameRec() const { return frameRec; };