#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.hpp"
#include "FilaDinamica.hpp"
#include "DeliveryPoint.hpp"
#include "Package.hpp"
#include "Cores.hpp"
#include "Bullet.hpp"

#include <cmath>
#include <vector>

class Player : public Entity 
{
private:
    const float velocity = 6.0f;
    float rotation = 30.0f; 

    const double shootInterval = 0.5f;
    float playerLastTimeFired;
    double shootCooldown;
    
    void drawQueue() const;
    std::vector<Bullet> bullets;
    

public: 
    Player(Vector2 position, float height, float width, std::string path) ;
    FilaDinamica filaEntrega;

    void Update(float deltaTime) override;
    void Draw() override;


    void Entregar(std::vector<DeliveryPoint>& circulos);
    void PegarItem (std::vector<Package>& retangulos);

    void Atirar();

}
;

#endif