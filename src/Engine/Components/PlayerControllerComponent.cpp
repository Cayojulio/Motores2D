#include "Engine/Components/PlayerControllerComponent.hpp"
#include <SDL3/SDL.h>
#include "Engine/Components/AnimationComponent.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Components/RectRenderComponent.hpp"

PlayerControllerComponent::PlayerControllerComponent(float spd, bool mouse_follow)
    : speed(spd), follow_mouse(mouse_follow)
{
}

void PlayerControllerComponent::FixedUpdate(float dt)
{
    if (!owner) return;
    auto* animComp = owner->GetComponent<AnimationComponent>();
    auto *transform = owner->GetComponent<TransformComponent>();
    if (!transform) return;
        if (!animComp) return;

    // 1. Lectura continua de teclado
    const bool *keys = SDL_GetKeyboardState(nullptr);
    Vector2 input_dir{0.0f, 0.0f};

    if (keys[SDL_SCANCODE_UP])    input_dir.y -= 1.0f;
    if (keys[SDL_SCANCODE_DOWN])  input_dir.y += 1.0f;
        if (keys[SDL_SCANCODE_RIGHT])  input_dir.x += 1.0f;
            if (keys[SDL_SCANCODE_LEFT])  input_dir.x -= 1.0f;
    Vector2 final_dir = input_dir;
    isMoving = (input_dir.length() > 0.0f);
    if (isMoving) {
    animComp->Play("WALK");
    animComp->Resume();
} else {
    animComp->Stop();              
    animComp->ResetToFirstFrame(); 
}

    // 2. Persecución del cursor del mouse
    if (follow_mouse)
    {
        Vector2 mouse_pos;
        SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);

        Vector2 center_offset{30.0f, 30.0f};
        if (auto *rect = owner->GetComponent<RectRenderComponent>())
        {
            center_offset = (rect->size * transform->scale.x) * 0.5f;
        }

        Vector2 mouse_dir = mouse_pos - (transform->position + center_offset);

        if (mouse_dir.length() >= 50.0f)
        {
            final_dir = input_dir + mouse_dir.normalized();
        }
    }

    // 3. Normalización del vector resultante
    if (final_dir.length_squared() > 0.01f)
    {
        final_dir = final_dir.normalized();
    }
    else
    {
        final_dir = {0.0f, 0.0f};
    }

    // 4. Traslación del transform
    Vector2 displacement = final_dir * (speed * dt);
    transform->Translate(displacement);


}
