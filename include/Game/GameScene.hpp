#pragma once

#include "Engine/Scene.hpp"
#include "Physics/CollisionManager.hpp"

class SceneManager;
class PauseScene;
class GameOverScene;

class GameScene : public Scene
{
private:
    CollisionManager m_collisionManager;
    bool m_debugDraw{false};
    GameObject* m_player2{nullptr};
    GameObject* m_player1{nullptr};

public:
    explicit GameScene(SceneManager *manager);

    void Init() override;
    void HandleEvent(const SDL_Event &event) override;
    void Update(float dt) override;
    void FixedUpdate (float Fixed_dt) override;
    void Render(SDL_Renderer *renderer) override;
};
