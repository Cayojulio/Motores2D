#pragma once

#include "Engine/Component.hpp"

class GameObject;

class PatrolComponent : public Component
{
public:
    float speed{10000.0f};
    float distance{300.0f};
    float origin_x{0.0f};
    float timer{0.0f};

    PatrolComponent(float spd, float dist);

    void Init() override;
    void Update(float dt) override;
};
