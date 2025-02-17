#ifndef PACKAGE_H
#define PACKAGE_H

#include "Entity.hpp"
#include "Cores.hpp"

class Package : public Entity 
{
private:
    Cores cor;
    float timer;
    const float respawnTime = 3.0f;
    
public:
    Package(Vector2 position, float height, float width, std::string path, int cor);
    
    Cores getCor() const;
    void Draw() override;
    void Update(float deltaTime) override;

}
;

#endif