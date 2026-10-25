#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Components/BotonComponent.hpp"
#include "Engine/Components/SpriteComponent.hpp"
void BotonComponent::Update(float dt) 
    {

        float mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        auto* transform = owner->GetComponent<TransformComponent>();
        auto* sprite = owner->GetComponent<SpriteComponent>();

        if (transform && sprite)
        {
            m_encima = (mouseX >= transform->position.x && 
                           mouseX <= transform->position.x + sprite->Ancho() &&
                           mouseY >= transform->position.y && 
                           mouseY <= transform->position.y + sprite->Altura());

        }
    }
