#include "Player.hpp"

Player::Player(Vector2 position, float height, float width, std::string path) 
: Entity (position, height, width, path)
{
    shootCooldown = 0;
    playerLastTimeFired = 0;
}

void Player::Update(float deltaTime)
{
    double currentShootTime = GetTime();

    if (IsKeyDown(KEY_RIGHT)) {
        frameRec.x += velocity;
        rotation += 180.0f * deltaTime;
    }    

    if (IsKeyDown(KEY_LEFT))  {
        frameRec.x -= velocity; 
        rotation -= 180.0f * deltaTime;
    }
    
    if (IsKeyDown(KEY_UP)) frameRec.y -= velocity;  
    if (IsKeyDown(KEY_DOWN)) frameRec.y += velocity;

    if (shootCooldown > 0.0f) {
        shootCooldown -= deltaTime;
    }

    if (IsKeyDown(KEY_SPACE) && (currentShootTime - playerLastTimeFired >= shootInterval)) {
        Bullet newBullet(position, 5, 5, "", rotation);
        bullets.push_back(newBullet);
        playerLastTimeFired = currentShootTime; 
    }

    for (auto &bullet : bullets) {
        bullet.Update(deltaTime);
    }

}

void Player::drawQueue() const
{
    int xPos = 20; 
    int yPos = 550; 

    for (int i = 0; i < filaEntrega.getQueueSize(); i++) {
        Cores cor = filaEntrega.getAt(i);
        Color color = (cor == Cores::VERMELHO) ? RED : (cor == Cores::VERDE) ? GREEN : BLUE;
        DrawRectangle(xPos, yPos, 30, 30, color);
        xPos += 40;
    }
}

void Player::Draw()
{
    Rectangle source = { 0, 0, 700, 700};
    Vector2 origin = { frameRec.width / 2, frameRec.height / 2 }; 

    // DrawTexturePro(texture, source, frameRec, (Vector2){0, 0}, 0.0f, WHITE);
    DrawTexturePro(texture, source, frameRec, origin, rotation, WHITE);

    drawQueue();

    for (auto& b : bullets) {
        b.Draw();
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