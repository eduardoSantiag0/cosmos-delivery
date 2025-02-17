#include "Package.hpp"

Package::Package(Vector2 position, float height, float width, std::string path, int cor)
: Entity (position, height, width, path), timer(0)
{
    // Cores novaCor;
    switch (cor) {
        case 0: this->cor  = Cores::VERMELHO; break;
        case 1: this->cor = Cores::VERDE; break;
        case 2: this->cor = Cores::AZUL; break;
    }
}

void Package::Draw()
{
    if (!active) return; 

    Color color;
    switch (cor) {
        case VERMELHO: color = RED; break;
        case VERDE: color = GREEN; break;
        case AZUL: color = BLUE; break;
        default: color = RED; break;  
    }

    DrawRectangleV(position, {20, 20}, color);
}


void Package::Update(float deltaTime)
{
    if (!active) {
        timer += deltaTime; 
        if (timer >= respawnTime) { 
            active = true;
            timer = 0; 
        }
    }
}

Cores Package::getCor() const { return this->cor; }