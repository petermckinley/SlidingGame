#include <SDL3/SDL.h>
#include <box2d/box2d.h>
#include <StaticEntity.hpp>
#include <iostream>

class GameWorld {
public:
    b2Vec2 playerPosition;
    int currentWorld;
    
    GameWorld() : currentWorld(1) {
        playerPosition.Set(0.0f, 0.0f);
    }


    void checkWorldTransition() {
        if (playerPosition.x >= 1000.0f) {
            changeWorld();
        }
    }

    // Function to change the world
    void changeWorld() {
        std::cout << "Changing to World " << currentWorld + 1 << std::endl;
        currentWorld++;
        resetPlayerPosition(); // Reset the player's position for the new world
    }

    // Reset player position when changing worlds
    void resetPlayerPosition() {
        playerPosition.Set(0.0f, 0.0f); // Reset to starting position
    }

    // Update player position based on game logic
    void updatePlayerPosition(float x, float y) {
        playerPosition.Set(x, y);
    }

    // You can add more conditions to the game as necessary for world transitions
};
