// Entity.cpp
#include "Entity.hpp"
#include "StaticEntity.hpp"
#define maxVel (30.0)

Entity::Entity(b2World& world, float x, float y, SDL_Texture* p_tex, float boxWidth, float boxHeight)
    : tex(p_tex), boxWidth(boxWidth), boxHeight(boxHeight) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);
    body = world.CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(boxWidth / 2.0f, boxHeight / 2.0f);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);
}

Entity::Entity(b2World& world, float x, float y, SDL_Texture* p_tex, float boxWidth, float boxHeight, b2Body* body)
    : tex(p_tex), boxWidth(boxWidth), boxHeight(boxHeight), body(body), staticBody(true) {}

Entity::Entity(b2World& world, StaticEntity& staticBody) :
    tex(staticBody.getTexture()),
    body(staticBody.getBody()),
    boxWidth(staticBody.getWidth()),
    boxHeight(staticBody.getHeight()),
    staticBody(true) {}

void Entity::applyForce(const b2Vec2& force) {
    body->ApplyForceToCenter(force, true);
}

void Entity::update() {
    // Physics is handled by Box2D, no manual position updates needed
}

void Entity::applyVelocityChange(const b2Vec2& vel) {
    if (body->GetLinearVelocity().x > maxVel) {
        b2Vec2 temp = b2Vec2(0.95 * maxVel, body->GetLinearVelocity().y);
        body->SetLinearVelocity(temp);
        return;
    } else if (body->GetLinearVelocity().x < -maxVel) {
        b2Vec2 temp = b2Vec2(-0.95 * maxVel, body->GetLinearVelocity().y);
        body->SetLinearVelocity(temp);
        return;
    }

    body->SetLinearVelocity(body->GetLinearVelocity() + vel);
}

SDL_Texture* Entity::get_Texture() {
    return tex;
}

b2Body* Entity::getBody() {
    return body;
}

Entity::Entity(b2World& world, b2Body* playerBody, SDL_Texture* p_tex, float radius)
    : tex(p_tex), boxWidth(radius * 2), boxHeight(radius * 2) {
    body = playerBody;
}