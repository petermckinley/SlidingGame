#ifndef RENDERWINDOW_HPP
#define RENDERWINDOW_HPP

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include "Entity.hpp"
#include "DraggableEntity.hpp"

class RenderWindow {
public:
    RenderWindow(const char* p_title, int p_w, int p_h);
    SDL_Texture* loadTexture(const char* p_filePath);
    void cleanUp();
    void clear();
    void render(Entity& p_ent);
    void render(StaticEntity& p_ent);
    void render(DraggableEntity& p_ent, bool isDragging, b2Vec2 offset);
    void display();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};
#endif