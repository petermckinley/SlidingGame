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

b2World* generateMenu(RenderWindow& window);
b2World* generateLevelOne(RenderWindow& window);

std::vector<b2World* (*)(RenderWindow&)> levels = {
    generateMenu,
    generateLevelOne
};

b2World* gameWorld;
b2World* menuWorld;
b2World* settingsWorld;
b2World* Currworld;
Entity* player = nullptr;

bool gameRunning = true;
SDL_Event event;
b2Body* selectedBody = nullptr;
b2Vec2 mouseOffset;

int currentLevel = 0;
int nextLevel = 0;


std::vector<DraggableEntity*> Dents;
std::vector<Entity> entities;
std::vector<StaticEntity*> Sents;

SDL_Texture* grassTexture;
SDL_Texture* bugTexture = window.loadTexture("../src/res/pixil-frame-0.png");
SDL_Texture* startTexture = window.loadTexture("../src/res/pxArt.png");

const float timestep = 1.0f / 60.0f;
const int velocityIterations = 6;
const int positionIterations = 2;

b2Vec2 localClickPoint;

void makePlayer(){
    b2CircleShape playerShape;
    playerShape.m_radius = 6.0f;

    b2BodyDef playerBodyDef;
    playerBodyDef.type = b2_dynamicBody;
    playerBodyDef.position.Set(60.0f / RFACTOR, 30.0f / RFACTOR);
    b2Body* playerBody = Currworld->CreateBody(&playerBodyDef);

    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &playerShape;
    playerFixtureDef.density = 1.0f;
    playerFixtureDef.friction = 0.5f;
    playerFixtureDef.restitution = 0.2f;

    playerBody->CreateFixture(&playerFixtureDef);

    player = new Entity(*Currworld, playerBody, bugTexture, 6.0f);
}


void changeWorld(){
    Sents.clear();
    Dents.clear();
    entities.clear();
    if(player) {
        delete player;
        player = nullptr;
    }
}

bool initialize(){
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
        return true;
    }
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

void handleEvents(std::vector<DraggableEntity*>& draggableEntities) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            gameRunning = false;
        } 
        else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT) {
            float mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            
            b2Vec2 mousePos(mouseX / RFACTOR, mouseY / RFACTOR);
            std::cout << mousePos.x << " " << mousePos.y << std::endl;

            for (DraggableEntity* d : draggableEntities) {
                b2Body* body = d->getBody();
                if (body) {
                    for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()) {
                        if (f->GetShape()->TestPoint(body->GetTransform(), mousePos)) {
                            selectedBody = body;

                            // Convert mousePos to local coordinates
                            b2Transform bodyTransform = body->GetTransform();
                            bodyTransform.q.c = -bodyTransform.q.c;
                            bodyTransform.q.s = bodyTransform.q.s;
                            b2Vec2 localMousePos = b2MulT(bodyTransform, mousePos);

                            localClickPoint = localMousePos; // Store the local click point
                            selectedBody = d->grab();
                            std::cout << "Object found!" << std::endl;
                            applyMouseForce(selectedBody, localClickPoint); // Pass localClickPoint
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
                    player->applyVelocityChange(b2Vec2(-3.0f, 0.0f));
                    break;
                case SDLK_RIGHT:
                    player->applyVelocityChange(b2Vec2(3.0f, 0.0f));
                    break;
                case SDLK_UP:
                    player->applyVelocityChange(b2Vec2(0.0f, -75.0f));
                    break;
                case SDLK_ESCAPE:
                    std::cout << "pressed";
                    gameRunning = false;
                    break;
                default:
                    std::cout << "Other key pressed" << std::endl;
                    break;
            }
        }
    }
}

b2World* generateMenu(RenderWindow& window){
    changeWorld();
    b2Vec2 gravity(0.0f, 90.8f);
    b2World* world = new b2World(gravity);
    
    //world 197.5 wide, 127.5 tall
    Sents.emplace_back(new StaticEntity(*world, 98.5, 110, grassTexture, 170, 10));
    Sents.emplace_back(new StaticEntity(*world, 15, 70, grassTexture, 10, 90));
    Sents.emplace_back(new StaticEntity(*world, 180, 70, grassTexture, 10, 90));

    entities.emplace_back(*world, 70, 60, startTexture, 20, 10);
    Dents.emplace_back(new DraggableEntity(*world, 80, 70, grassTexture, 10, 10));
    Dents.emplace_back(new DraggableEntity(*world, 60, 70, grassTexture, 10, 10));
    

    return world;
}

b2World* generateLevelOne(RenderWindow& window) {
    changeWorld();
    b2Vec2 gravity(0.0f, 90.8f);
    b2World* world = new b2World(gravity);

    grassTexture = window.loadTexture("../src/res/ground_grass_1.png");

    Sents.emplace_back(new StaticEntity(*world, 0, WINDOW_HEIGHT / (6 * RFACTOR), grassTexture, WINDOW_WIDTH * 2 / RFACTOR, 20.0f));
    Sents.emplace_back(new StaticEntity(*world, WINDOW_WIDTH / RFACTOR, 0, grassTexture, 10, WINDOW_HEIGHT / RFACTOR));
    Sents.emplace_back(new StaticEntity(*world, 0, WINDOW_HEIGHT * 6 / (8 * RFACTOR), grassTexture, WINDOW_WIDTH * 2 / RFACTOR, WINDOW_HEIGHT / (8 * RFACTOR)));


    //Ents.emplace_back(*world, 100.0f, 3.0f, grassTexture, 3.0f, 3.0f);
    //Ents.emplace_back(*world, 10.0f, 30.0f, grassTexture, 6.0f, 3.0f);
    //Ents.emplace_back(*world, 3.0f, 10.0f, grassTexture, 3.0f, 3.0f);
    //Ents.emplace_back(*world, 10.0f, 10.0f, grassTexture, 3.0f, 3.0f);

    Dents.emplace_back(new DraggableEntity(*world, 100.0f, 50.0f, grassTexture, 4.0f, 4.0f));
    Dents.emplace_back(new DraggableEntity(*world, 100.0f, 25.0f, grassTexture, 4.0f, 4.0f));
    Dents.emplace_back(new DraggableEntity(*world, 100.0f, 10.0f, grassTexture, 4.0f, 4.0f));

    return world;
}

void getCurrentLevel(){
    if (currentLevel == 0){
        if (true){
            return;
        }
    }
    
    return;
}

void gameloop(){
    getCurrentLevel();//goes to indiviaul level data and checks if level is over
    handleEvents(Dents);
    //make teleporter to the center of world if peice falls off side
    Currworld->Step(timestep, velocityIterations, positionIterations);

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

void run_menu(RenderWindow& window) {
    changeWorld();
    Currworld = levels[0](window); // Call generateMenu
    makePlayer();
    entities.emplace_back(*player);

    while (gameRunning) {
        gameloop();

        if (currentLevel != nextLevel) {
            Currworld = levels[nextLevel](window);
        }
    }
}

int main(int argc, char* args[]) {
    if (initialize()){
        std::cout << "bad error: end program" << std::endl;
        return 0;
    }

    Currworld = generateMenu(window);
    //Currworld = generateLevelOne(entities, Sents, Dents, window);

    makePlayer();
    entities.emplace_back(*player);

    while (gameRunning) {
        run_menu(window);
    }

    window.cleanUp();
    SDL_Quit();

    return 0;
}