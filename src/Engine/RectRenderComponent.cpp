#include "Engine/RectRenderComponent.hpp"
#include "Engine/GameObject.hpp"         
#include "Engine/TransformComponent.hpp"

RectRenderComponent::RectRenderComponent(Vector2 s, SDL_Color c)
    : size(s), color(c)
{
}


void RectRenderComponent::Render(SDL_Renderer *renderer)
{
    if (!renderer || !owner) return;

    auto *transform = owner->GetComponent<TransformComponent>();
    if (!transform) return;

    SDL_FRect rect{
        transform->position.x,
        transform->position.y,
        size.x * transform->scale.x,
        size.y * transform->scale.y
    };

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}
