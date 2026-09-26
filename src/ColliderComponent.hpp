#pragma once

#include "Component.hpp"
#include "GameObject.hpp"
#include "TransformComponent.hpp"
#include "Vector2.hpp"

class ColliderComponent : public Component
{
public:
    Vector2 offset{0.0f, 0.0f};
    Vector2 size{60.0f, 60.0f};
    bool is_trigger{false};
    bool is_colliding{false};
    ColliderComponent(Vector2 size) : size(size) {}
    SDL_FRect GetWorldBounds() const 
    {
   
        if (owner == nullptr) {
            return SDL_FRect{ offset.x, offset.y, size.x, size.y };
        }

      
        TransformComponent* transform = owner->GetComponent<TransformComponent>();

        // Redimensionamos 
        if (transform != nullptr) {
            float x = transform->position.x + offset.x;
            float y = transform->position.y + offset.y;
            float w = size.x * transform->scale.x;
            float h = size.y * transform->scale.y;

            return SDL_FRect{ x, y, w, h };
        }

        
        return SDL_FRect{ offset.x, offset.y, size.x, size.y };
    }
    void RenderDebug(SDL_Renderer *renderer)
{
    if (renderer == nullptr) return;
    
    SDL_FRect bounds = GetWorldBounds();

   if (is_colliding) {
        SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
    }
    else {

        SDL_SetRenderDrawColor(renderer, 50, 255, 50, 255);
    }
    SDL_RenderRect(renderer, &bounds);
}
   
};
