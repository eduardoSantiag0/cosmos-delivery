#include "raylib.h"
#include <iostream> 
#include "Player.hpp"
#include "DeliveryPoint.hpp"
#include "Package.hpp"


int main() {
  const int screenWidth = 800;
  const int screenHeight = 600;
  InitWindow(screenWidth, screenHeight, "Serviço de Entregas");

  const int spacing = 100;

  Vector2 centerScreen = { (float)screenWidth/2, (float)screenHeight/2 };

  Player player = Player(centerScreen, 80, 80, "resources/player-spaceship-2.png");

  DeliveryPoint entregaVermelha = DeliveryPoint ({250, 200}, 40, 40, "", 0);
  DeliveryPoint entregaVerde = DeliveryPoint ({250 + spacing, 200}, 40, 40, "", 1);
  DeliveryPoint entregaAzul = DeliveryPoint ({250 + spacing*2, 200}, 40, 40, "", 2);
  std::vector<DeliveryPoint> vetorPontosEntrega = {entregaVermelha, entregaVerde, entregaAzul};

  Package pacoteVermelho = Package({150, 100}, 40, 40, "", 0);
  Package pacoteVerde = Package({150, 100+spacing}, 40, 40, "", 1);
  Package pacoteAzul = Package({150, 100+spacing*2}, 40, 40, "", 2);
  std::vector<Package> vetorPacotes = {pacoteVermelho, pacoteVerde, pacoteAzul};

  Texture2D background = LoadTexture("resources/background.png");


  SetTargetFPS(60);
  while (!WindowShouldClose()) {

    float deltaTime = GetFrameTime();
        
    // Update
    //-------------------------------

    player.Update(deltaTime);

    for (Package& p: vetorPacotes) 
      p.Update(deltaTime);
    

    for (DeliveryPoint& d: vetorPontosEntrega)
      d.Update(deltaTime);

    player.PegarItem(vetorPacotes);
    player.Entregar(vetorPontosEntrega);


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

      player.Draw();

      DrawText("Serviço de Entregas!", 20, 20, 20, YELLOW);
    
    EndDrawing();
  }

  UnloadTexture(background);
  CloseWindow();
  return 0;

}
