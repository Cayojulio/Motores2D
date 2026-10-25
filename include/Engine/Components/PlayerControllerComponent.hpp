#pragma once

#include "Engine/Component.hpp"
#include "Math/Vector2.hpp"

class GameObject;
class TransformComponent;
class RectRenderComponent;

class PlayerControllerComponent : public Component
{
public:
    float speed{300.0f};
    bool follow_mouse{true};

    PlayerControllerComponent() = default;
    explicit PlayerControllerComponent(float spd, bool mouse_follow = true);

    void FixedUpdate(float dt) override;
};
