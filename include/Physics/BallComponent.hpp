#pragma once

#include "Engine/Component.hpp"
#include "Math/Vector2.hpp"

class GameObject;

class BallComponent : public Component
{
public:
    Vector2 velocity{220.0f, 180.0f};

    BallComponent() = default;

    void FixedUpdate(float dt) override;
    void OnCollision(GameObject *other) override;
};
