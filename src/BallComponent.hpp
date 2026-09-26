#pragma once

#include "Component.hpp"
#include "GameObject.hpp"
#include "Vector2.hpp"
#include "TransformComponent.hpp"
#include "RectRenderComponent.hpp"

class BallComponent : public Component
{
public:
    Vector2 velocity{220.0f, 180.0f};

    void Update(float dt) override
    {
        if (owner == nullptr) return;
        auto* transform = owner->GetComponent<TransformComponent>();
        auto* render = owner->GetComponent<RectRenderComponent>();

        if (transform == nullptr || render == nullptr) return;
        transform->Translate(velocity * dt);

        // Limites en X
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

    void OnCollision(GameObject *other) override
    {
        if (owner == nullptr || other == nullptr) return;

        auto* transformPelota = owner->GetComponent<TransformComponent>();
        auto* renderPelota = owner->GetComponent<RectRenderComponent>();

        auto* transformOtro = other->GetComponent<TransformComponent>();
        auto* renderOtro = other->GetComponent<RectRenderComponent>();

        if (!transformPelota || !renderPelota || !transformOtro || !renderOtro) return;

        //calculamos los centros
        Vector2 c_pelota{
            transformPelota->position.x + (renderPelota->size.x * 0.5f),
            transformPelota->position.y + (renderPelota->size.y * 0.5f)
        };

        Vector2 c_otro{
            transformOtro->position.x + (renderOtro->size.x * 0.5f),
            transformOtro->position.y + (renderOtro->size.y * 0.5f)
        };

        Vector2 d = c_pelota - c_otro;
        
      
        if (std::abs(d.x) > std::abs(d.y))
        {
           
            velocity.x = (d.x > 0.0f) ? std::abs(velocity.x) : -std::abs(velocity.x);
        }
        else
        {
           
            velocity.y = (d.y > 0.0f) ? std::abs(velocity.y) : -std::abs(velocity.y);
        }
       SDL_Log("Colisión");
    }
};
