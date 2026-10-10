	#include "Physics/PatrolComponent.hpp"
#include <cmath>
#include "Engine/GameObject.hpp"
#include "Engine/TransformComponent.hpp"

PatrolComponent::PatrolComponent(float spd, float dist)
    : speed(spd), distance(dist)
{
}

void Init()
{
}

void PatrolComponent::Init()
{
    if (!owner) return;

    if (auto *t = owner->GetComponent<TransformComponent>())
    {
        origin_x = t->position.x;
    }
}

void PatrolComponent::Update(float dt)
{
    if (!owner) return;

    if (auto *t = owner->GetComponent<TransformComponent>())
    {
        timer += dt * (speed / 50.0f);
        t->position.x = origin_x + std::sin(timer) * distance;
    }
}
