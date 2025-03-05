#ifndef STATIC_BODY_HPP
#define STATIC_BODY_HPP

#include <SDL3/SDL.h>
#include <box2d/box2d.h>

class StaticEntity {
public:
    StaticEntity(b2World& world, float x, float y, SDL_Texture* p_tex, float boxWidth, float boxHeight);
    ~StaticEntity(); // Destructor to clean up Box2D body

    SDL_Texture* getTexture() const;
    b2Body* getBody() const;
    float getWidth() const;
    float getHeight() const;

private:
    SDL_Texture* tex;
    b2Body* body;
    float boxWidth;
    float boxHeight;
};

#endif 