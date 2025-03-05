#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SDL3/SDL.h>
#include <box2d/box2d.h>
#include <StaticEntity.hpp>

class Entity {
public:
    Entity(b2World& world, float x, float y, SDL_Texture* p_tex, float boxWidth, float boxHeight);
    Entity(b2World& world, float x, float y, SDL_Texture* p_tex, float boxWidth, float boxHeight, b2Body* body);
    Entity(b2World& world, StaticEntity& staticBody);
    void applyForce(const b2Vec2& force);
    void applyVelocityChange(const b2Vec2& vel);
    void update();
    SDL_Texture* get_Texture();
    b2Body* getBody();
    float getbW() {return boxWidth;}
    float getbH() {return boxHeight;}
    bool isStatic() { return staticBody;}

private:
    SDL_Texture* tex;
    b2Body* body;
    float boxWidth;
    float boxHeight;
    bool staticBody = false;
};

#endif