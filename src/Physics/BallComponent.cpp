#include "Physics/BallComponent.hpp"
#include <cmath>
#include <SDL3/SDL.h>

#include "Engine/GameObject.hpp"
#include "Engine/TransformComponent.hpp"
#include "Engine/RectRenderComponent.hpp"
#include "Physics/ColliderComponent.hpp"

void BallComponent::FixedUpdate(float dt)
{
    if (owner == nullptr) return;

    auto *transform = owner->GetComponent<TransformComponent>();
    auto *render = owner->GetComponent<RectRenderComponent>();

    if (transform == nullptr || render == nullptr) return;

    transform->Translate(velocity * dt);

 
    if (transform->position.x <= 0.0f)
    {
        velocity.x = std::abs(velocity.x);
        transform->position.x = 0.0f;
    }
    else if (transform->position.x >= (960.0f - render->size.x))
    {
        velocity.x = -std::abs(velocity.x);
        transform->position.x = 960.0f - render->size.x;
    }

    // Límites en Y
    if (transform->position.y <= 0.0f)
    {
        velocity.y = std::abs(velocity.y);
        transform->position.y = 0.0f;
    }
    else if (transform->position.y >= (540.0f - render->size.y))
    {
        velocity.y = -std::abs(velocity.y);
        transform->position.y = 540.0f - render->size.y;
    }
}

void BallComponent::OnCollision(GameObject *other) 
{
    if (owner == nullptr || other == nullptr) return;

    auto* transformPelota = owner->GetComponent<TransformComponent>();
    auto* colliderPelota = owner->GetComponent<ColliderComponent>();

    auto* transformOtro = other->GetComponent<TransformComponent>();
    auto* colliderOtro = other->GetComponent<ColliderComponent>();


    if (!transformPelota || !colliderPelota || !transformOtro || !colliderOtro) return;


    SDL_FRect rectPelota = colliderPelota->GetWorldBounds();
    SDL_FRect rectOtro = colliderOtro->GetWorldBounds();


    float centroPelotaX = rectPelota.x + (rectPelota.w * 0.5f);
    float centroPelotaY = rectPelota.y + (rectPelota.h * 0.5f);

    float centroOtroX = rectOtro.x + (rectOtro.w * 0.5f);
    float centroOtroY = rectOtro.y + (rectOtro.h * 0.5f);


    float diffX = centroPelotaX - centroOtroX;
    float diffY = centroPelotaY - centroOtroY;

    float overlapX = (rectPelota.w * 0.5f) + (rectOtro.w * 0.5f) - std::abs(diffX);
    float overlapY = (rectPelota.h * 0.5f) + (rectOtro.h * 0.5f) - std::abs(diffY);


    if (overlapX < overlapY)
    {

        if (diffX > 0.0f)
        {
            velocity.x = std::abs(velocity.x); 
            transformPelota->position.x += overlapX;
        }
        else
        {
            velocity.x = -std::abs(velocity.x); 
            transformPelota->position.x -= overlapX; 
        }
    }
    else
    {
       
        if (diffY > 0.0f)
        {
            velocity.y = std::abs(velocity.y);
            transformPelota->position.y += overlapY;
        }
        else
        {
            velocity.y = -std::abs(velocity.y); 
            transformPelota->position.y -= overlapY; 
        }
    }
    
    
    
    velocity.x *= 1.10f;
    velocity.y *= 1.10f;

    float velocidadMaxima = 600.0f;
    

    if (std::abs(velocity.x) > velocidadMaxima) 
    {
        velocity.x = (velocity.x > 0.0f) ? velocidadMaxima : -velocidadMaxima;
    }

    if (std::abs(velocity.y) > velocidadMaxima) 
    {
        velocity.y = (velocity.y > 0.0f) ? velocidadMaxima : -velocidadMaxima;
    }
    if (std::abs(velocity.y) >= velocidadMaxima){
    SDL_Log("llegaste");
    }

    SDL_Log("Colision");
}
