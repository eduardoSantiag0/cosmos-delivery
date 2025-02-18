#include "Player.hpp"

Player::Player(Vector2 position, float height, float width, std::string path) 
: Entity (position, height, width, path)
{
    rotation = 0.0f;
    shootCooldown = 0;
    playerLastTimeFired = 0;
    speed = 0; 
    acceleration = 0;  
    maxSpeed = 200; 
    maxAcceleration = 250;  
    velocity = 0;
    score = 0;
}

void Player::accelerate(const float delta)
{
    acceleration += delta;
    if (acceleration > maxAcceleration) {
        acceleration = maxAcceleration;
    }
    if (acceleration < -maxAcceleration) {
        acceleration = -maxAcceleration;
    }
}

void Player::decelerate(const float delta)
{
    acceleration -= delta;
    if (acceleration < 0) {
        acceleration = 0;
    }

    if (acceleration > 0) {
        acceleration -= delta;
        if (acceleration < 0) acceleration = 0;
    }
}

void Player::Update(float deltaTime)
{
    double currentShootTime = GetTime();

    if (IsKeyDown(KEY_RIGHT)) {
        rotation += 180.0f * deltaTime;
    }    

    if (IsKeyDown(KEY_LEFT)) {
        // accelerate(-5);
        rotation -= 180.0f * deltaTime;
    }

    if (IsKeyDown(KEY_UP)) {
        accelerate(10);
    }

    if (IsKeyDown(KEY_DOWN)) {
        accelerate(-10);

    }

    if (!IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN)) {
        decelerate(10 * deltaTime);
    }


    speed += acceleration * deltaTime;

    if (speed > maxSpeed) {
        speed = maxSpeed;
    }
    if (speed < 0) {
        speed = 0;
    }


    float angle = (rotation - 90) * DEG2RAD;  
    frameRec.x += speed * cos(angle) * deltaTime;
    frameRec.y += speed * sin(angle) * deltaTime;

    if (IsKeyDown(KEY_SPACE) && (currentShootTime - playerLastTimeFired >= shootInterval)) {                
        Bullet newBullet({frameRec.x, frameRec.y}, 10, 10, "resources/bullet-white.png", rotation - 90.0f);
        bullets.push_back(newBullet);
        playerLastTimeFired = currentShootTime;
    }


    if (shootCooldown > 0.0f) {
        shootCooldown -= deltaTime;
    }

    for (auto &bullet : bullets) {
        bullet.Update(deltaTime);
    }

    if (frameRec.x < 0) frameRec.x = 800;
    if (frameRec.x > 800) frameRec.x = 0;
    if (frameRec.y < 0) frameRec.y = 600;
    if (frameRec.y > 600) frameRec.y = 0;
}

void Player::drawQueue() const
{
    int xPos = 20; 
    int yPos = 550; 

    for (int i = 0; i < filaEntrega.getQueueSize(); i++) {
        Cores cor = filaEntrega.getAt(i);
        // Cores cor = static_cast<Cores>(filaEntrega.getAt(i));
        Color color = (cor == Cores::VERMELHO) ? RED : (cor == Cores::VERDE) ? GREEN : BLUE;
        DrawRectangle(xPos, yPos, 30, 30, color);
        xPos += 40;
    }
}

void Player::Draw()
{
    Rectangle source = { 0, 0, 700, 700};
    Vector2 origin = { frameRec.width / 2, frameRec.height / 2 }; 

    DrawTexturePro(texture, source, frameRec, origin, rotation, WHITE);

    drawQueue();

    for (int i = bullets.size() - 1; i >= 0; i--) {
        if (!bullets[i].isActive()) {
            bullets.erase(bullets.begin() + i);
        } else {
            bullets[i].Draw();
        }
    }
        
}


void Player::Entregar(std::vector<DeliveryPoint> &circulos) {

    if (!filaEntrega.estaVazia()) {
        for (DeliveryPoint &circulo : circulos) 
        {
            if (CheckCollisionRecs(circulo.getFrameRec(), frameRec) 
            && filaEntrega.mostrarFrente() == circulo.getCor()) 
            {
                filaEntrega.desenfileirar();
                this->addPontos(100);
                std::cout << "Entrega feita!" << std::endl;
                break;
            }
        }
    }

}

void Player::PegarItem(std::vector<Package> &retangulos) 
{
    for (size_t i = 0; i < retangulos.size(); i++) {
        if (CheckCollisionRecs(frameRec, retangulos[i].getFrameRec()) && retangulos[i].isActive()) {
            retangulos[i].Deactivate();
            filaEntrega.enfileirar(i);
            std::cout << "Item Pegado!" << std::endl;
            break;
        }
    }
}


void Player::addPontos(int pontosGanhos)
{
    score += pontosGanhos;
}

int Player::getScore() const 
{
    return this->score;
}