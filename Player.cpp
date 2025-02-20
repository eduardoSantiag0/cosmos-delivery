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
    vidas = 3;
    inserir(laserBasico.nome, laserBasico.intervaloDeTiro);
}

// Player::~Player()
// {
//     UnloadTexture(texture);
// }

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
    const Weapon* armaAtual = obterMaior();

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

    if (score >= 100 && heap.size() < 2) inserir(canhaoDePlasma.nome, canhaoDePlasma.intervaloDeTiro);
    if (score >= 250 && heap.size() < 3) inserir(metralhadora.nome, metralhadora.intervaloDeTiro);
    if (score >= 500 && heap.size() < 4) inserir(bazuca.nome, bazuca.intervaloDeTiro);
    if (score >= 1000 && heap.size() < 5) inserir(pistolaPlasma.nome, pistolaPlasma.intervaloDeTiro);


    if (IsKeyDown(KEY_SPACE) && (currentShootTime - playerLastTimeFired >= armaAtual->intervaloDeTiro)) {                
        Bullet newBullet({frameRec.x, frameRec.y}, 10, 10, "resources/bullet-white.png", rotation - 90.0f);
        bullets.push_back(newBullet);
        playerLastTimeFired = currentShootTime;
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

    for (int i = 0; i < vidas; i++) {
        DrawRectangle(GetScreenWidth() - (40 * (i + 1)), 20, 30, 30, PURPLE);
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
            filaEntrega.enfileirar(retangulos[i].getCor());
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

int Player::getVidas() const 
{
    return this->vidas;
}


void Player::perdeuVida()  
{
    this->vidas--;
}

void Player::heapifyUp(int index) {
    while (index > 0) {
        int pai = (index - 1) / 2;
        if (heap[index].intervaloDeTiro < heap[pai].intervaloDeTiro) { // CORRIGIDO: Menor intervalo sobe
            std::swap(heap[index], heap[pai]);
            index = pai;
        } else {
            break;
        }
    }
}

void Player::heapifyDown(int index) {
    int tamanho = heap.size();
    while (true) {
        int menor = index;
        int esq = 2 * index + 1;
        int dir = 2 * index + 2;

        if (esq < tamanho && heap[esq].intervaloDeTiro < heap[menor].intervaloDeTiro)
            menor = esq;
        if (dir < tamanho && heap[dir].intervaloDeTiro < heap[menor].intervaloDeTiro)
            menor = dir;

        if (menor != index) {
            std::swap(heap[index], heap[menor]);
            index = menor;
        } else {
            break;
        }
    }
}

bool Player::inserir(const std::string& nome, double cadencia) {
    heap.push_back(Weapon{nome, cadencia});
    heapifyUp(heap.size() - 1);
    return true;
}

bool Player::removerMax() {
    if (heap.empty()) return false;

    std::swap(heap[0], heap.back());
    heap.pop_back();
    heapifyDown(0);
    return true;
}

const Weapon* Player::obterMaior() const {
    if (heap.empty()) return nullptr;
    return &heap[0];
}

void Player::exibir() const {
    for (const auto& arma : heap) {
        std::cout << arma.nome << ", Cadência: " << arma.intervaloDeTiro << ")\n";
    }
    std::cout << std::endl;
}
