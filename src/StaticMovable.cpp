#include "StaticMovable.hpp"

StaticMovable::StaticMovable(b2World& world, float x, float y, SDL_Texture* p_tex, float boxWidth, float boxHeight)
    : tex(p_tex), boxWidth(boxWidth), boxHeight(boxHeight) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody; // Set body type to static
    bodyDef.position.Set(x, y);

    body = world.CreateBody(&bodyDef);

    b2PolygonShape staticBox;
    staticBox.SetAsBox(boxWidth / 2.0f, boxHeight / 2.0f);

    body->CreateFixture(&staticBox, 0.0f); // 0.0f density for static bodies
}

StaticMovable::~StaticMovable() {
    if (body) {
        body->GetWorld()->DestroyBody(body);
        body = nullptr;
    }
}

SDL_Texture* StaticMovable::getTexture() const {
    return tex;
}

b2Body* StaticMovable::getBody() const {
    return body;
}

float StaticMovable::getWidth() const {
    return boxWidth;
}

float StaticMovable::getHeight() const {
    return boxHeight;
}

void mouseDrag(){
    
}