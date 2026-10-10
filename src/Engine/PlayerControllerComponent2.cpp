#include "Engine/PlayerControllerComponent2.hpp"
#include <SDL3/SDL.h>
#include <cmath>

#include "Engine/GameObject.hpp"
#include "Engine/TransformComponent.hpp"
#include "Engine/RectRenderComponent.hpp"

PlayerControllerComponent2::PlayerControllerComponent2(float spd, bool mouse_follow, bool Act)
    : speed(spd), follow_mouse(mouse_follow), Activar(Act)
{
}

void PlayerControllerComponent2::FixedUpdate(float dt)
{
    if (!owner) return;
    const bool *keys = SDL_GetKeyboardState(nullptr);
    auto *transform = owner->GetComponent<TransformComponent>();
    if (!transform) return;

    Vector2 final_dir{0.0f, 0.0f};
    //AUtomatico
    if (Activar)
    {
        if (m_ballTransform)
        {
            float player_center_y = transform->position.y;
            if (auto *rect = owner->GetComponent<RectRenderComponent>())
            {
                player_center_y += (rect->size.y * transform->scale.y) * 0.5f;
            }

            float ball_center_y = m_ballTransform->position.y;
            float diff_y = ball_center_y - player_center_y;

            constexpr float DEADZONE = 5.0f;

            if (std::abs(diff_y) > DEADZONE)
            {
                final_dir.y = (diff_y > 0.0f) ? 1.0f : -1.0f;
            }
        }
    }
    else
    {
    //manual
        const bool *keys = SDL_GetKeyboardState(nullptr);

        if (keys[SDL_SCANCODE_W]) final_dir.y -= 1.0f;
        if (keys[SDL_SCANCODE_S]) final_dir.y += 1.0f;
    }

    // Normalización de dirección
    if (final_dir.length_squared() > 0.01f)
    {
        final_dir = final_dir.normalized();
    }

    // Aplicar traslación
    Vector2 displacement = final_dir * (speed * dt);
    transform->Translate(displacement);

    // Delimitar dentro de los bordes de la ventana (960 x 540)
    Vector2 max_bounds{960.0f, 540.0f};
    if (auto *rect = owner->GetComponent<RectRenderComponent>())
    {
        max_bounds = max_bounds - (rect->size * transform->scale.x);
    }
    transform->position = transform->position.clamp(Vector2{0.0f, 0.0f}, max_bounds);
}
