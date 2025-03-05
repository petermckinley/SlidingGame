#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <iostream>
#include <vector>
#include <box2d/box2d.h>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"
#include "StaticEntity.hpp"

#define RFACTOR (8)
#define WINDOW_HEIGHT (1020)
#define WINDOW_WIDTH  (1580)

int main(int argc, char* args[]) {
    if (!   SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
        return 1;
    }

    RenderWindow window("GAME v1.0", WINDOW_WIDTH, WINDOW_HEIGHT);

    //World Entities
////////////////////////////////////////////////////////////////////////////////
    SDL_Texture* grassTexture = window.loadTexture("../src/res/ground_grass_1.png");

    SDL_Texture* bugTexture = window.loadTexture("../src/res/pixil-frame-0.png");

    if (grassTexture == nullptr || bugTexture == nullptr) {
      std::cout << "Failed to load grass texture." << std::endl;
      window.cleanUp();
      SDL_Quit();
      return 1;
    }

    b2Vec2 gravity(0.0f, 90.8f);
    b2World world(gravity);

    StaticEntity grd(world, 0, WINDOW_HEIGHT / (6* RFACTOR), grassTexture, WINDOW_WIDTH* 2 / RFACTOR, 20.0f);

    StaticEntity leftWall(world, 0.0, 0.0, grassTexture, 10.0f, WINDOW_HEIGHT);
    StaticEntity rightWall(world, WINDOW_WIDTH / RFACTOR, 0, grassTexture, 10, WINDOW_HEIGHT);

    StaticEntity groundBox(world, 0, WINDOW_HEIGHT * 6 / (8 * RFACTOR), grassTexture, WINDOW_WIDTH * 2 / RFACTOR, WINDOW_HEIGHT / (8 * RFACTOR));
    Entity player(world, 60.0f, 30.0f, bugTexture, 6.0f, 12.0f);

    std::vector<Entity> entities = {
        Entity(world, 100.0f, 3.0f, grassTexture, 3.0f, 3.0f),
        Entity(world, 10.0f, 30.0f, grassTexture, 6.0f, 3.0f),
        Entity(world, 3.0f, 10.0f, grassTexture, 3.0f, 3.0f),
        Entity(world, 10.0f, 10.0f, grassTexture, 3.0f, 3.0f),
        player,
        Entity(world, grd),
        Entity(world, groundBox),
        Entity(world, leftWall),
        Entity(world, rightWall)
    };

////////////////////////////////////////////////////////////////////////////////

    
    bool gameRunning = true;
    SDL_Event event;

    const float timestep = 1.0f / 60.0f; // 60 Hz simulation
    const int velocityIterations = 6;
    const int positionIterations = 2;

    while (gameRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                gameRunning = false;
            } else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT) {
                float mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                float box2DX = static_cast<float>(mouseX) / RFACTOR;
                float box2DY = static_cast<float>(mouseY) / RFACTOR;
                
                for (int i = 0; i < RFACTOR; i++) {
                    entities.emplace_back(world, box2DX, box2DY, grassTexture, 6.0f, 6.0f);
                }
            } else if (event.type == SDL_EVENT_KEY_DOWN) {
                switch (event.key.key) {
                    case SDLK_LEFT:
                        player.applyVelocityChange(b2Vec2(-2.0f,0.0f));
                        break;
                    case SDLK_RIGHT:
                        player.applyVelocityChange(b2Vec2(2.0f,0.0f));
                        break;
                    case SDLK_UP:
                        player.applyVelocityChange(b2Vec2(0.0f,-75.0f));
                        break;
                    case SDLK_ESCAPE:
                        gameRunning = false;
                        break;
                    default:
                        std::cout << "Other key pressed" << std::endl;
                        break;
                }
            }
        }

        world.Step(timestep, velocityIterations, positionIterations);

        window.clear();
        for (Entity& e : entities) {
            window.render(e);
        }
        window.display();
    }

    window.cleanUp();
    SDL_DestroyTexture(grassTexture);
    SDL_Quit();

    return 0;
}