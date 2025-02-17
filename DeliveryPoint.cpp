#include "DeliveryPoint.hpp"

DeliveryPoint::DeliveryPoint(Vector2 position, float height, float width, std::string path, int cor)
: Entity (position, height, width, path)
{
    // Cores novaCor;
    switch (cor) {
        case 0: this->cor  = Cores::VERMELHO; break;
        case 1: this->cor = Cores::VERDE; break;
        case 2: this->cor = Cores::AZUL; break;
    }
}

void DeliveryPoint::Draw()
{
    Color color;
    switch (cor) {
        case VERMELHO: color = RED; break;
        case VERDE: color = GREEN; break;
        case AZUL: color = BLUE; break;
        default: color = RED; break;  
    }
    DrawCircle(frameRec.x, frameRec.y, 20, color);
}


void DeliveryPoint::Update(float deltaTime)
{
    
}

Cores DeliveryPoint::getCor() const { return this->cor; }