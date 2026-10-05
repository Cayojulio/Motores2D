#pragma once


#include "Scene.hpp"
#include "SceneManager.hpp"
#include "CollisionManager.hpp"
#include "GameObject.hpp"

#include "TransformComponent.hpp"
#include "RectRenderComponent.hpp"
#include "PlayerControllerComponent.hpp"
#include "ColliderComponent.hpp"
#include "BallComponent.hpp"


class PauseScene;
class GameOverScene;

class GameScene : public Scene
{
private:
    CollisionManager m_collisionManager;
    bool m_debugDraw{false};

public:
    explicit GameScene(SceneManager *manager)
        : Scene(manager, "GameScene"),
        m_collisionManager(&m_entities)
    {
    }

    void Init() override;
    void HandleEvent(const SDL_Event &event) override;
    void Update(float dt) override;
    void Render(SDL_Renderer *renderer) override;
};

#include "PauseScene.hpp"
#include "GameOverScene.hpp"


inline void GameScene::Init()
{
    m_entities.clear();
    m_collisionManager.SetEntities(&m_entities);

    // Player
    auto player = std::make_unique<GameObject>("Player");
player->AddComponent<TransformComponent>(Vector2{440.0f, 240.0f});
player->AddComponent<RectRenderComponent>(Vector2{60.0f, 60.0f},
SDL_Color{60, 180, 100, 255});
player->AddComponent<PlayerControllerComponent>(300.0f, false);
player->AddComponent<ColliderComponent>(Vector2{60.0f,60.0f});
    m_entities.push_back(std::move(player));

    // Obstacle
    auto obstacle = std::make_unique<GameObject>("obstacle");
obstacle->AddComponent<TransformComponent>(Vector2{180.0f, 140.0f});
obstacle->AddComponent<RectRenderComponent>(Vector2{80.0f, 80.0f}, SDL_Color{220, 70, 70, 255});
obstacle->AddComponent<ColliderComponent>(Vector2{80.0f, 80.0f});
    m_entities.push_back(std::move(obstacle));

    // Pelota
    auto Pelota = std::make_unique<GameObject>("Pelota");
Pelota->AddComponent<TransformComponent>(Vector2{468.0f, 80.0f});
Pelota->AddComponent<RectRenderComponent>(Vector2{24.0f, 24.0f},
SDL_Color{220, 210, 60, 255});
Pelota->AddComponent<ColliderComponent>(Vector2{24.0f,24.0f});
Pelota->AddComponent<BallComponent>();
    m_entities.push_back(std::move(Pelota));
}

inline void GameScene::HandleEvent(const SDL_Event &event)
{
    Scene::HandleEvent(event);

    if (event.type == SDL_EVENT_KEY_DOWN)
    {
        switch (event.key.key)
        {
            case SDLK_F1:
                m_debugDraw = !m_debugDraw;
                SDL_Log("Debug Draw: %s", m_debugDraw ? "ACTIVADO" : "DESACTIVADO");
                break;

            case SDLK_P:
            case SDLK_ESCAPE:
                if (m_manager)
                {
                    m_manager->PushScene(std::make_unique<PauseScene>(m_manager));
                }
                break;

            case SDLK_G:
                if (m_manager)
                {
                    m_manager->ChangeScene(std::make_unique<GameOverScene>(m_manager));
                }
                break;

            default:
                break;
        }
    }
}

inline void GameScene::Update(float dt)
{
    Scene::Update(dt);
    m_collisionManager.CheckCollisions();
}

inline void GameScene::Render(SDL_Renderer *renderer)
{
    if (!renderer) return;

    SDL_SetRenderDrawColor(renderer, 25, 25, 30, 255);
    SDL_RenderClear(renderer);

    Scene::Render(renderer);

    if (m_debugDraw)
    {
        for (auto &entity : m_entities)
        {
            if (entity && entity->IsActive())
            {
                if (auto *col = entity->GetComponent<ColliderComponent>())
                {
                    col->RenderDebug(renderer);
                }
            }
        }
    }
}
