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

void handleEvents(SDL_Event& event, bool& gameRunning, b2World* world, b2Body*& selectedBody, b2Vec2& mouseOffset, Entity& player) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            gameRunning = false;
        } 
        else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT) {
            float mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            
            b2Vec2 mousePos(mouseX / RFACTOR, mouseY / RFACTOR);

            // Query Box2D world for bodies at this position
            struct QueryCallback : public b2QueryCallback {
                b2Vec2 mousePos;
                b2Body* foundBody = nullptr;

                QueryCallback(const b2Vec2& pos) : mousePos(pos) {}

                bool ReportFixture(b2Fixture* fixture) override {
                    b2Body* body = fixture->GetBody();
                    if (body->GetType() == b2_dynamicBody) {
                        foundBody = body;
                        return false;
                    }
                    return true;
                }
            } query(mousePos);

            b2AABB aabb;
            aabb.lowerBound = mousePos - b2Vec2(0.1f, 0.1f);
            aabb.upperBound = mousePos + b2Vec2(0.1f, 0.1f);

            world->QueryAABB(&query, aabb);

            if (query.foundBody) {
                selectedBody = query.foundBody;
                mouseOffset = selectedBody->GetPosition() - mousePos; // Store offset
            }
        } 
        else if (event.type == SDL_EVENT_MOUSE_MOTION && selectedBody) {
            float mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            
            b2Vec2 newMousePos(mouseX / RFACTOR, mouseY / RFACTOR);
            b2Vec2 targetPos = newMousePos + mouseOffset;

            b2Vec2 impulse = targetPos - selectedBody->GetPosition();
            impulse *= selectedBody->GetMass(); // Scale based on mass

            selectedBody->ApplyLinearImpulseToCenter(impulse, true);
        } 
        else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP && event.button.button == SDL_BUTTON_LEFT) {
            selectedBody = nullptr;
        } 
        else if (event.type == SDL_EVENT_KEY_DOWN) {
            switch (event.key.key) {
                case SDLK_LEFT:
                    player.applyVelocityChange(b2Vec2(-2.0f, 0.0f));
                    break;
                case SDLK_RIGHT:
                    player.applyVelocityChange(b2Vec2(2.0f, 0.0f));
                    break;
                case SDLK_UP:
                    player.applyVelocityChange(b2Vec2(0.0f, -75.0f));
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
}


b2World* generateLevelOne(std::vector<Entity>& Ents, std::vector<StaticEntity*>& StaticEnts, RenderWindow& window) {
    b2Vec2 gravity(0.0f, 90.8f);
    b2World* world = new b2World(gravity);

    SDL_Texture* grassTexture = window.loadTexture("../src/res/ground_grass_1.png");

    // Create StaticEntities dynamically to avoid object slicing
    StaticEnts.emplace_back(new StaticEntity(*world, 0, WINDOW_HEIGHT / (6 * RFACTOR), grassTexture, WINDOW_WIDTH * 2 / RFACTOR, 20.0f));
    StaticEnts.emplace_back(new StaticEntity(*world, WINDOW_WIDTH / RFACTOR, 0, grassTexture, 10, WINDOW_HEIGHT / RFACTOR));
    StaticEnts.emplace_back(new StaticEntity(*world, 0, WINDOW_HEIGHT * 6 / (8 * RFACTOR), grassTexture, WINDOW_WIDTH * 2 / RFACTOR, WINDOW_HEIGHT / (8 * RFACTOR)));

    // Store dynamic entities separately
    Ents.emplace_back(*world, 100.0f, 3.0f, grassTexture, 3.0f, 3.0f);
    Ents.emplace_back(*world, 10.0f, 30.0f, grassTexture, 6.0f, 3.0f);
    Ents.emplace_back(*world, 3.0f, 10.0f, grassTexture, 3.0f, 3.0f);
    Ents.emplace_back(*world, 10.0f, 10.0f, grassTexture, 3.0f, 3.0f);

    return world;
}


int main(int argc, char* args[]) {
    if (!   SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
        return 1;
    }

    RenderWindow window("GAME v1.0", WINDOW_WIDTH, WINDOW_HEIGHT);
    b2World* world;
    SDL_Texture* bugTexture = window.loadTexture("../src/res/pixil-frame-0.png");


    std::vector<Entity> entities;
    std::vector<StaticEntity*> Sents;
    world = generateLevelOne(entities, Sents, window);
    Entity player (*world, 60.0f, 30.0f, bugTexture, 6.0f, 12.0f);
    entities.emplace_back(player);
    //World Entities
////////////////////////////////////////////////////////////////////////////////
/*
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
/////
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
*/
////////////////////////////////////////////////////////////////////////////////

    
    bool gameRunning = true;
    SDL_Event event;

    const float timestep = 1.0f / 60.0f; // 60 Hz simulation
    const int velocityIterations = 6;
    const int positionIterations = 2;

    b2Body* selectedBody = nullptr;
    b2Vec2 mouseOffset;


    while (gameRunning) {
        handleEvents(event, gameRunning, world, selectedBody, mouseOffset, player);
        world->Step(timestep, velocityIterations, positionIterations);

        window.clear();
        for (Entity& e : entities) {
            window.render(e);
        }
        for (StaticEntity* e : Sents){
            window.render(*e);
        }
        window.display();
    }

    window.cleanUp();
    //SDL_DestroyTexture(grassTexture);
    SDL_Quit();

    return 0;
}