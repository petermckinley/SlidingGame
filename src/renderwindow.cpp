#include "RenderWindow.hpp"
#include <iostream>
#define RFACTOR (8)

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
    : window(NULL), renderer(NULL) {
    window = SDL_CreateWindow(p_title, p_w, p_h, 0);

    if (window == NULL) {
        std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, NULL);
    SDL_SetRenderVSync(renderer, true);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, p_filePath);

    if (texture == NULL)
        std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

    return texture;
}

void RenderWindow::cleanUp() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void RenderWindow::clear() {
    SDL_SetRenderDrawColor(renderer, 60, 85, 120, 255);
    SDL_RenderClear(renderer);
}

void RenderWindow::render(StaticEntity& s_ent) {
    b2Body* body = s_ent.getBody();
    if (body == nullptr) {
        return; // Skip rendering if there's no body
    }

    b2Vec2 position = body->GetPosition();
    SDL_Texture* texture = s_ent.getTexture();
    float width = s_ent.getWidth();
    float height = s_ent.getHeight();

    if (texture == nullptr) {
        std::cout << "No texture provided for static entity" << std::endl;
        return; // Skip rendering if there's no texture
    }

    SDL_FRect src;
    src.x = 0;
    src.y = 0;

    SDL_PropertiesID textureProperties = SDL_GetTextureProperties(texture);
    if (textureProperties == 0) {
        std::cerr << "Error getting texture properties: " << SDL_GetError() << std::endl;
        return;
    }

    float textureWidth, textureHeight;
    if (!SDL_GetTextureSize(texture, &textureWidth, &textureHeight)) {
        std::cerr << "Error getting texture dimensions: " << SDL_GetError() << std::endl;
        return; 
    }

    src.w = textureWidth;
    src.h = textureHeight;

    SDL_FRect dst;
    dst.x = position.x * RFACTOR - (width * RFACTOR / 2);
    dst.y = position.y * RFACTOR - (height * RFACTOR / 2);
    dst.w = width * RFACTOR;
    dst.h = height * RFACTOR;

    SDL_RenderTexture(renderer, texture, &src, &dst);
}

void RenderWindow::render(Entity& p_ent) {
    b2Body* body = p_ent.getBody();
    if (body == nullptr) {
        return; // Nothing to render if there's no body.
    }

    b2Vec2 position = body->GetPosition();
    float angle = body->GetAngle();

    SDL_Texture* texture = p_ent.get_Texture();
    float width = p_ent.getbW();
    float height = p_ent.getbH();

    if (texture == nullptr) {
        std::cout << "no texture provided" << std::endl;
        return; // Nothing to render if there's no texture.
    }

    SDL_FRect src;
    src.x = 0;
    src.y = 0;
    
    SDL_PropertiesID textureProperties = SDL_GetTextureProperties(texture);
    if (textureProperties == 0) {
        std::cerr << "Error getting texture properties: " << SDL_GetError() << std::endl;
        return; // Handle error, possibly return or use default dimensions
    }

    float textureWidth, textureHeight;
    if (!SDL_GetTextureSize(texture, &textureWidth, &textureHeight)) {
        std::cerr << "Error getting texture dimensions: " << SDL_GetError() << std::endl;
        return; 
    }

    src.w = textureWidth;
    src.h = textureHeight;

    SDL_FRect dst;
    dst.x = position.x * RFACTOR - (width * RFACTOR / 2);
    dst.y = position.y * RFACTOR - (height * RFACTOR / 2);
    dst.w = width * RFACTOR;
    dst.h = height * RFACTOR;

    SDL_RenderTextureRotated(renderer, texture, &src, &dst, angle * 180.0f / b2_pi, NULL, SDL_FLIP_NONE);

}

void RenderWindow::display() {
    SDL_RenderPresent(renderer);
}