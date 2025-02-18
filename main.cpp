#include "raylib.h"
#include <iostream> 
#include "Player.hpp"
#include "DeliveryPoint.hpp"
#include "Package.hpp"
#include "Asteroid.hpp"

using namespace std;

int main() {
  const int screenWidth = 800;
  const int screenHeight = 600;
  InitWindow(screenWidth, screenHeight, "Serviço de Entregas");

  const int spacing = 100;

  Vector2 centerScreen = { (float)screenWidth/2, (float)screenHeight/2 };

  Player player = Player(centerScreen, 80, 80, "resources/player-spaceship-2.png");

  // Inicializando pontos de entrega, pacotes e asteroides
  std::vector<DeliveryPoint> vetorPontosEntrega;
  double lastDeliverySpawnTime = GetTime();
  const double deliverySpawnInterval = 10.0;
  const double deliveryLifetime = 10.0;

  std::vector<Package> vetorPacotes;
  double lastPackageSpawnTime = GetTime();
  const double packageSpawnInterval = 6.0;
  const int maxPackages = 5;

  std::vector<Asteroid> asteroids;
  double lastAsteroidSpawnTime = GetTime();
  const double asteroidSpawnInterval = 6.0; 
  const int maxSpawnAsteroid = 6;
  
  Texture2D background = LoadTexture("resources/background.png");

  bool gameStarted = false;

  SetTargetFPS(60);
  while (!WindowShouldClose()) {

    float deltaTime = GetFrameTime();
    
    // Tela inicial
    if (!gameStarted) {
      BeginDrawing();
      ClearBackground(BLACK);
      DrawTextureEx(background, (Vector2){0, 0}, 0, 1.0f, WHITE);
      player.Draw();
      DrawText("SPACE para começar e atirar.", 200, 300, 30, WHITE);
      EndDrawing();

      if (IsKeyPressed(KEY_SPACE)) {
          gameStarted = true;
      }
      continue;
  }
    // Update
    //-------------------------------

    player.Update(deltaTime);

    for (Package& p: vetorPacotes) 
      p.Update(deltaTime);
    

    for (DeliveryPoint& d: vetorPontosEntrega)
      d.Update(deltaTime);

    player.PegarItem(vetorPacotes);
    player.Entregar(vetorPontosEntrega);

    for (Asteroid& asteroid : asteroids) {
      asteroid.Update(deltaTime);
    }

    // Gera um novo asteroide após o tempo especificado
    if (GetTime() - lastAsteroidSpawnTime >= asteroidSpawnInterval && asteroids.size() < maxSpawnAsteroid) {
      int corner = GetRandomValue(0, 3);
      Vector2 asteroidPos;
      switch (corner) {
          case 0: asteroidPos = {0, 0}; break; // Canto superior esquerdo
          case 1: asteroidPos = {screenWidth - 1, 0}; break; // Canto superior direito
          case 2: asteroidPos = {0, screenHeight - 1}; break; // Canto inferior esquerdo
          case 3: asteroidPos = {screenWidth - 1, screenHeight - 1}; break; // Canto inferior direito
      }

        float size = (float)GetRandomValue(40, 80);
        float speed = (float)GetRandomValue(100, 200);
        float rotationSpeed = (float)GetRandomValue(30, 60);
        asteroids.emplace_back(asteroidPos, size, size, "resources/asteroid.png", speed, rotationSpeed);
        lastAsteroidSpawnTime = GetTime();
    }

    // Gera novos DeliveryPoints aleatoriamente com tempo de expiração
    if (GetTime() - lastDeliverySpawnTime >= deliverySpawnInterval) {
        float x = (float)GetRandomValue(0, screenWidth - 40);
        float y = (float)GetRandomValue(0, screenHeight - 40);
        int color = GetRandomValue(0, 2);
        DeliveryPoint dp(Vector2{x, y}, 40, 40, "", color);
        dp.creationTime = GetTime();
        vetorPontosEntrega.push_back(dp);
        std::cout << "DeliveryPoint Criado" << std::endl;
        lastDeliverySpawnTime = GetTime();
    }

    // Remove DeliveryPoints expirados
    for (int i = vetorPontosEntrega.size() - 1; i >= 0; i--) {
        if (GetTime() - vetorPontosEntrega[i].creationTime > deliveryLifetime) {
            vetorPontosEntrega.erase(vetorPontosEntrega.begin() + i);
            std::cout << "DeliveryPoint Expirado" << std::endl;
        }
    }

    //???? ERRO
  // Gera novos Packages aleatoriamente
  if (GetTime() - lastPackageSpawnTime >= packageSpawnInterval && vetorPacotes.size() < maxPackages) {
      float x = (float)GetRandomValue(0, screenWidth - 40);
      float y = (float)GetRandomValue(0, screenHeight - 40);
      int color = GetRandomValue(0, 2);
      // Cores color = static_cast<Cores>(GetRandomValue(0, 2));
      vetorPacotes.emplace_back(Vector2{x, y}, 40, 40, "", color);
      std::cout << "Package Criado" << std::endl;
      lastPackageSpawnTime = GetTime();
  }

    // Verifica colisão entre balas e asteroides
    for (auto& bullet : player.bullets) {
      for (auto& asteroid : asteroids) {
          if (CheckCollisionRecs(bullet.getFrameRec(), asteroid.getFrameRec())) {
              asteroid.Deactivate();
              bullet.Deactivate();
              player.addPontos(10);
          }
      }
    }
    // Drawing
    // -------------------------------
    BeginDrawing();

      ClearBackground(DARKPURPLE);

      DrawTextureEx(background, (Vector2){0, 0}, 0, 1.0f, WHITE);
        
      for (Package& pacote : vetorPacotes) {
          pacote.Draw();
      }

      for (DeliveryPoint& ponto : vetorPontosEntrega) {
          ponto.Draw();
      }

      for (Asteroid& asteroid : asteroids) {
        if (asteroid.isActive()) {
            asteroid.Draw();
        }
      }
      
      player.Draw();


      DrawText("Cosmos Delivery!", 20, 20, 20, YELLOW);
      DrawText(TextFormat("Pontuação: %d", player.getScore()), 20, 50, 30, WHITE);
    
    EndDrawing();

    for (int i = asteroids.size() - 1; i >= 0; i--) {
      if (!asteroids[i].isActive()) {
          asteroids.erase(asteroids.begin() + i);
      } else {
          asteroids[i].Draw();
      }
    }
  }

  UnloadTexture(background);
  CloseWindow();
  return 0;

}
