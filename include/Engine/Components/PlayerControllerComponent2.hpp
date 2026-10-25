#pragma once

#include "Engine/Component.hpp"
#include "Physics/BallComponent.hpp"
class TransformComponent;

class PlayerControllerComponent2 : public Component
{
public:
    float speed{300.0f};
    bool follow_mouse{false};
    bool Activar{false}; 

private:
    TransformComponent *m_ballTransform{nullptr};
    BallComponent *m_ball{nullptr};

public:
    PlayerControllerComponent2() = default;
    
    PlayerControllerComponent2(float spd, bool mouse_follow = false, bool Act = false);

    void BallTransform(TransformComponent *ballTransform)
    {
        m_ballTransform = ballTransform;
    }
    void BallComponent1(BallComponent *Ball)
    {
        m_ball= Ball;
    }

    void FixedUpdate(float dt) override;
};
