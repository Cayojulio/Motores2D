#pragma once

#include <SDL3/SDL.h>
#include "Engine/Component.hpp"
#include "Math/Vector2.hpp"

class ColliderComponent : public Component
{
public:
    Vector2 offset{0.0f, 0.0f};
    Vector2 size{60.0f, 60.0f};
    bool is_trigger{false};
    bool is_colliding{false};

    ColliderComponent() = default;
    explicit ColliderComponent(Vector2 size);

    SDL_FRect GetWorldBounds() const;
    void RenderDebug(SDL_Renderer *renderer);
};
