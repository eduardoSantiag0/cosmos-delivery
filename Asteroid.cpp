#include "Asteroid.hpp"
#include <iostream>

Asteroid::Asteroid(Vector2 position, float height, float width, std::string path, float speed, float rotationSpeed)
    : Entity(position, height, width, path), speed(speed), rotation(0.0f), rotationSpeed(rotationSpeed)
{
    directionAngle = GetRandomValue(0, 360) * DEG2RAD;
}

void Asteroid::Update(float deltaTime)
{
    if (!active) return;

    frameRec.x += speed * cos(directionAngle) * deltaTime;
    frameRec.y += speed * sin(directionAngle) * deltaTime;

    rotation += rotationSpeed * deltaTime;
    if (rotation >= 360.0f) rotation -= 360.0f;

    if (frameRec.x < -frameRec.width) frameRec.x = GetScreenWidth();
    if (frameRec.x > GetScreenWidth()) frameRec.x = -frameRec.width;
    if (frameRec.y < -frameRec.height) frameRec.y = GetScreenHeight();
    if (frameRec.y > GetScreenHeight()) frameRec.y = -frameRec.height;
}

void Asteroid::Draw()
{
    if (!active) return;

    // Usa a textura completa, ajustada ao tamanho especificado no construtor
    Rectangle source = { 0, 0, (float)texture.width, (float)texture.height }; // Usa o tamanho completo da textura
    Rectangle dest = { frameRec.x, frameRec.y, frameRec.width, frameRec.height }; // Ajusta ao tamanho desejado
    Vector2 origin = { frameRec.width / 2, frameRec.height / 2 }; // Origem no centro para rotação correta

    // Desenha a textura com o tamanho correto e rotação
    DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
}
