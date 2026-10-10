#include "Engine/VidasComponent.hpp"
#include <SDL3/SDL.h>
#include <algorithm>

#include "Engine/GameObject.hpp"
#include "Engine/TransformComponent.hpp"
#include "Physics/BallComponent.hpp"

VidasComponent::VidasComponent(int vidas, LadoCampo lado)
    : Vidas_Totales(vidas), Vidas_Actual(vidas), ladoDefendido(lado)
{
}

void VidasComponent::Daño()
{
    Vidas_Actual = std::clamp(Vidas_Actual - 1, 0, Vidas_Totales);
}

void VidasComponent::Reset()
{
    Vidas_Actual = Vidas_Totales;
}

void VidasComponent::Update(float dt)
{
   if (!m_ballTransform) return;
    bool golEnContra = false;

    if (ladoDefendido == LadoCampo::Izquierda && m_ballTransform->position.x <= 10.0f)
    {
        golEnContra = true;
    }
    else if (ladoDefendido == LadoCampo::Derecha && m_ballTransform->position.x >= 920.0f) 
    {
        golEnContra = true;
    }

    if (golEnContra)
    {
        Daño();

       
        m_ballTransform->position = Vector2{468.0f, 258.0f};

        if (auto* ballComp = m_ballTransform->owner->GetComponent<BallComponent>())
        {
            ballComp->velocity.x = -220.0f;
            ballComp->velocity.y = -180.0f;
        }
    }
}

void VidasComponent::Render(SDL_Renderer* renderer)
{
    if (!owner || Vidas_Actual <= 0 || renderer == nullptr) return;

    TransformComponent* transform = owner->GetComponent<TransformComponent>();
    if (!transform) return;

    float X = posicion.x;
    float Y = posicion.y;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    for (int i = 0; i < Vidas_Actual; ++i)
    {
        
        SDL_FRect Barras{
            X + (i * (bar_size.x + spacing)),
            Y,
            bar_size.x,
            bar_size.y
        };

        SDL_RenderFillRect(renderer, &Barras);
    }
}
