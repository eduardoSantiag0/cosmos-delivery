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
    float velocity = 6.0f;
    float rotation; 

    // Thurst
    float speed = 0;  // Initial speed
    float acceleration = 0;  // Initial acceleration
    float maxSpeed = 200;  // Set a max speed for the player
    float maxAcceleration = 100;  // Set max acceleration for the player

    double shootInterval = 0.4f;
    float playerLastTimeFired;
    double shootCooldown;

    int score;
    
    void drawQueue() const;
    
    
public: 
    std::vector<Bullet> bullets;
    Player(Vector2 position, float height, float width, std::string path) ;
    FilaDinamica filaEntrega;

    void Update(float deltaTime) override;
    void Draw() override;

    void Entregar(std::vector<DeliveryPoint>& circulos);
    void PegarItem (std::vector<Package>& retangulos);

    void accelerate(float delta);
    void decelerate(float delta);

    void addPontos(int pontosGanhos);
    int getScore() const;

}
;

#endif