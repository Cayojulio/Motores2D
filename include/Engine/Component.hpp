#pragma once

#include <SDL3/SDL.h>

// Declaración anticipada (Forward Declaration)
class GameObject;

class Component
{
public:
// Puntero de vuelta al padre
GameObject *owner{nullptr};
// Destructor virtual
virtual ~Component() = default;
virtual void OnCollision(GameObject *other) {}
// Métodos virtuales del ciclo de vida
virtual void Init() {}
virtual void Update(float dt) {}
virtual void FixedUpdate(float fixed_dt) {}
virtual void Render(SDL_Renderer *renderer) {}
};
