all: 
	g++ main.cpp Entity.cpp Player.cpp FilaDinamica.cpp Package.cpp DeliveryPoint.cpp Bullet.cpp -o main -std=c++11 -Wall -Wextra -g -lstdc++ -lraylib -lopengl32 -lgdi32 -lwinmm
