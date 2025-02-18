#ifndef DELIVERY_POINT_H
#define DELIVERY_POINT_H

#include "Entity.hpp"
#include "Cores.hpp"

class DeliveryPoint : public Entity 
{
private:
    Cores cor;
    
public:
    
    double creationTime;
    
    DeliveryPoint(Vector2 position, float height, float width, std::string path, int cor);
    Cores getCor() const;
    void Draw() override;
    void Update(float deltaTime) override;
}
;

#endif