#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <iostream>
#include <vector>
#include <box2d/box2d.h>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"
#include "StaticEntity.hpp"
#include "DraggableEntity.hpp"

#define RFACTOR (8)
#define WINDOW_HEIGHT (1020)
#define WINDOW_WIDTH  (1580)
RenderWindow window("GAME v1.0", WINDOW_WIDTH, WINDOW_HEIGHT);
b2World* gameWorld;
b2World* menuWorld;
b2World* settingsWorld;

std::vector<DraggableEntity*> Dents;
std::vector<Entity> entities;
std::vector<StaticEntity*> Sents;

SDL_Texture* grassTexture;
SDL_Texture* bugTexture;

const float timestep = 1.0f / 60.0f;
const int velocityIterations = 6;
const int positionIterations = 2;

bool initialize(){
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
        return true;
    }
    bugTexture = window.loadTexture("../src/res/pixil-frame-0.png");
    grassTexture = window.loadTexture("../src/res/ground_grass_1.png");
    return false;
}

void applyMouseForce(b2Body* selectedBody, b2Vec2 mouseOffset){
    float mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    selectedBody->SetGravityScale(0.0f);

    
    b2Vec2 mousePos(mouseX / RFACTOR, mouseY / RFACTOR);
    b2Vec2 targetPos = mousePos + mouseOffset;

    b2Vec2 currentPos = selectedBody->GetPosition();
    b2Vec2 velocity = selectedBody->GetLinearVelocity();

    float k = 800.0f;
    float d = 500.0f;

    b2Vec2 force = (targetPos - currentPos);
    force.x *= k;
    force.y *= k;
    
    b2Vec2 dampingForce = velocity;
    dampingForce.x *= d;
    dampingForce.y *= d;
    
    force -= dampingForce;

    selectedBody->ApplyForceToCenter(force, true);
}

void handleEvents(SDL_Event& event, bool& gameRunning, b2World* world, b2Body*& selectedBody, b2Vec2& mouseOffset, Entity& player, std::vector<DraggableEntity*>& draggableEntities) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            gameRunning = false;
        } 
        else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT) {
            float mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            
            b2Vec2 mousePos(mouseX / RFACTOR, mouseY / RFACTOR);

            for (DraggableEntity* d : draggableEntities) {
                b2Body* body = d->getBody();
                if (body) {
                    for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()) {
                        if (f->GetShape()->TestPoint(body->GetTransform(), mousePos)) {
                            selectedBody = body;
                            mouseOffset = selectedBody->GetPosition() - mousePos;
                            selectedBody = d->grab();
                            std::cout << "Object found!" << std::endl;
                            applyMouseForce(selectedBody, mouseOffset);
                            break;
                        }
                    }
                }
            }
            
        } 
        else if (event.type == SDL_EVENT_MOUSE_MOTION && selectedBody) {
            applyMouseForce(selectedBody, mouseOffset);
        } 
        else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP && event.button.button == SDL_BUTTON_LEFT) {
            for (DraggableEntity* d : draggableEntities) {
                if (d->getBody() == selectedBody) {
                    d->release();
                    break;
                }
            }
            selectedBody = nullptr;
        } 
        else if (event.type == SDL_EVENT_KEY_DOWN) {
            switch (event.key.key) {
                case SDLK_LEFT:
                    player.applyVelocityChange(b2Vec2(-3.0f, 0.0f));
                    break;
                case SDLK_RIGHT:
                    player.applyVelocityChange(b2Vec2(3.0f, 0.0f));
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

b2World* generateLevelOne(std::vector<Entity>& Ents, std::vector<StaticEntity*>& StaticEnts, std::vector<DraggableEntity*>& DraggableEnts, RenderWindow& window) {
    b2Vec2 gravity(0.0f, 90.8f);
    b2World* world = new b2World(gravity);

    grassTexture = window.loadTexture("../src/res/ground_grass_1.png");

    //StaticEnts.emplace_back(new StaticEntity(*world, 0, WINDOW_HEIGHT / (6 * RFACTOR), grassTexture, WINDOW_WIDTH * 2 / RFACTOR, 20.0f));
    //StaticEnts.emplace_back(new StaticEntity(*world, WINDOW_WIDTH / RFACTOR, 0, grassTexture, 10, WINDOW_HEIGHT / RFACTOR));
    StaticEnts.emplace_back(new StaticEntity(*world, 0, WINDOW_HEIGHT * 6 / (8 * RFACTOR), grassTexture, WINDOW_WIDTH * 2 / RFACTOR, WINDOW_HEIGHT / (8 * RFACTOR)));


    //Ents.emplace_back(*world, 100.0f, 3.0f, grassTexture, 3.0f, 3.0f);
    //Ents.emplace_back(*world, 10.0f, 30.0f, grassTexture, 6.0f, 3.0f);
    //Ents.emplace_back(*world, 3.0f, 10.0f, grassTexture, 3.0f, 3.0f);
    //Ents.emplace_back(*world, 10.0f, 10.0f, grassTexture, 3.0f, 3.0f);

    DraggableEnts.emplace_back(new DraggableEntity(*world, 100.0f, 50.0f, grassTexture, 4.0f, 4.0f));
    DraggableEnts.emplace_back(new DraggableEntity(*world, 100.0f, 25.0f, grassTexture, 4.0f, 4.0f));
    DraggableEnts.emplace_back(new DraggableEntity(*world, 100.0f, 10.0f, grassTexture, 4.0f, 4.0f));

    return world;
}


int main(int argc, char* args[]) {
    if (initialize()){
        std::cout << "bad error: end program" << std::endl;
        return 0;
    }

    b2World* world;
    world = generateLevelOne(entities, Sents, Dents, window);

    Entity player (*world, 60.0f, 30.0f, bugTexture, 6.0f, 12.0f);
    entities.emplace_back(player);

    bool gameRunning = true;
    SDL_Event event;

    b2Body* selectedBody = nullptr;
    b2Vec2 mouseOffset;

    while (gameRunning) {
        handleEvents(event, gameRunning, world, selectedBody, mouseOffset, player, Dents);
        world->Step(timestep, velocityIterations, positionIterations);

        window.clear();
        bool isDragging = (selectedBody != nullptr);
        b2Vec2 offset = (isDragging && selectedBody) ? mouseOffset : b2Vec2(0, 0);

        for (DraggableEntity* e : Dents) {
            window.render(*e, isDragging, offset);
        }
        for (Entity& e : entities) {
            window.render(e);
        }
        for (StaticEntity* e : Sents){
            window.render(*e);
        }
        window.display();
    }

    window.cleanUp();
    SDL_Quit();

    return 0;
}