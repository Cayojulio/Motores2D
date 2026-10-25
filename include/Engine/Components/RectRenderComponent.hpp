#pragma once

#include "Engine/Component.hpp"
#include "Math/Vector2.hpp"
#include <SDL3/SDL.h>

class GameObject;

class RectRenderComponent : public Component
{
public:
    Vector2 size{30.0f, 30.0f};
    SDL_Color color{255, 255, 255, 255};

    RectRenderComponent() = default;
    RectRenderComponent(Vector2 s, SDL_Color c);

    void Render(SDL_Renderer *renderer); 
};
