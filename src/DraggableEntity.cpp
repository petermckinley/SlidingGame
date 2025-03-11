#include "DraggableEntity.hpp"

DraggableEntity::DraggableEntity(b2World& world, float x, float y, SDL_Texture* p_tex, float boxWidth, float boxHeight)
    : world(world), tex(p_tex), boxWidth(boxWidth), boxHeight(boxHeight) {
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(x, y);

    body = world.CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(boxWidth / 2.0f, boxHeight / 2.0f);

    body->CreateFixture(&shape, 0.0f); 
}

DraggableEntity::~DraggableEntity() {
    if (body) {
        world.DestroyBody(body);
        body = nullptr;
    }
}

b2Body* DraggableEntity::grab() {
    if (body->GetType() == b2_staticBody) {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position = body->GetPosition();
        bodyDef.angle = body->GetAngle();
        b2Body* newBody = world.CreateBody(&bodyDef);

        for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()) {
            newBody->CreateFixture(f->GetShape(), 1.0f); // Copy fixture
        }

        world.DestroyBody(body);
        body = newBody;
    }
    return body;
}

void DraggableEntity::release() {
    if (body->GetType() == b2_dynamicBody) {
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position = body->GetPosition();
        bodyDef.angle = body->GetAngle();
        b2Body* newBody = world.CreateBody(&bodyDef);

        for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext()) {
            newBody->CreateFixture(f->GetShape(), 0.0f);
        }

        world.DestroyBody(body);
        body = newBody;
    }
}

void DraggableEntity::setPosition(float x, float y) {
    body->SetTransform(b2Vec2(x, y), body->GetAngle());
}

SDL_Texture* DraggableEntity::getTexture() const {
    return tex;
}

b2Body* DraggableEntity::getBody() const {
    return body;
}

float DraggableEntity::getWidth() const {
    return boxWidth;
}

float DraggableEntity::getHeight() const {
    return boxHeight;
}
