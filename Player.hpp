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

struct Weapon {
    std::string nome;
    double intervaloDeTiro;
    int pontuacao;
};

class Player : public Entity 
{
private:
    float velocity = 6.0f;
    float rotation; 

    float speed = 0;  
    float acceleration = 0;  
    float maxSpeed = 200;  
    float maxAcceleration = 100;  

    double shootInterval = 0.4f;
    float playerLastTimeFired;
    double shootCooldown;

    int score;
    std::vector<Weapon> heap;

    int vidas;
    
    void drawQueue() const;

    Weapon laserBasico = {"Laser Básico", 0.7, 0};
    Weapon canhaoDePlasma = {"Canhão de Plasma", 0.6, 1000};
    Weapon metralhadora = {"Metralhadora", 0.5, 2500};
    Weapon bazuca = {"Bazuca", 0.4, 5000};
    Weapon pistolaPlasma = {"Pistola Plasma", 0.3, 10000}; 
    
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

    int getVidas() const;
    void perdeuVida();

    void heapifyUp(int index);
    void heapifyDown(int index);
    bool inserir(const std::string& nome, double cadencia);
    bool removerMax();
    const Weapon* obterMaior() const;
    void exibir() const;
}
;

#endif