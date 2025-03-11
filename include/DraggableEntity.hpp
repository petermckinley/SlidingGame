#ifndef DRAGGABLEENTITY_HPP
#define DRAGGABLEENTITY_HPP

#include <box2d/box2d.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>

class DraggableEntity {
    public:
        DraggableEntity(b2World& world, float x, float y, SDL_Texture* p_tex, float boxWidth, float boxHeight);
        ~DraggableEntity();
    
        b2Body* grab();
        void release();
        void setPosition(float x, float y);
    
        SDL_Texture* getTexture() const;
        b2Body* getBody() const;
        float getWidth() const;
        float getHeight() const;
    
    private:
        b2World& world;
        b2Body* body;
        SDL_Texture* tex;
        float boxWidth, boxHeight;
    };

#endif
