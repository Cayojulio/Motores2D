#include "Game/GameScene.hpp"
#include <memory>
#include <SDL3/SDL.h>

#include "Engine/SceneManager.hpp"
#include "Engine/VidasComponent.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/TransformComponent.hpp"
#include "Engine/RectRenderComponent.hpp"
#include "Engine/PlayerControllerComponent.hpp"
#include "Physics/ColliderComponent.hpp"
#include "Physics/PatrolComponent.hpp"
#include "Physics/BallComponent.hpp"
#include "Game/PauseScene.hpp"
#include "Game/GameOverScene.hpp"
#include "Engine/PlayerControllerComponent2.hpp"

GameScene::GameScene(SceneManager *manager)
    : Scene(manager, "GameScene"),
      m_collisionManager(&m_entities)
{
}

void GameScene::Init()
{
    m_entities.clear();
    m_collisionManager.SetEntities(&m_entities);

// Pelota
    auto pelota = std::make_unique<GameObject>("Pelota");
    auto* ballTransform = pelota->AddComponent<TransformComponent>(Vector2{468.0f, 80.0f});
    pelota->AddComponent<RectRenderComponent>(Vector2{10.0f, 10.0f}, SDL_Color{255, 255, 255, 255});
    pelota->AddComponent<ColliderComponent>(Vector2{10.0f, 10.0f});
    pelota->AddComponent<BallComponent>();
    m_entities.push_back(std::move(pelota));

//Player 1
    auto player = std::make_unique<GameObject>("Player");
    player->AddComponent<TransformComponent>(Vector2{100.0f, 0.0f});
    player->AddComponent<RectRenderComponent>(Vector2{15.0f, 50.0f}, SDL_Color{255, 255, 255, 255});
    player->AddComponent<PlayerControllerComponent>(500.0f, false);
    player->AddComponent<ColliderComponent>(Vector2{15.0f, 50.0f});
    auto* vidas1 = player->AddComponent<VidasComponent>(7, LadoCampo::Izquierda);
    vidas1->BallTransform(ballTransform);
    vidas1->PosicionarBarras(Vector2{30.0f, 20.0f});
    m_player1 = player.get();
    m_entities.push_back(std::move(player));


// Player2
    auto player2 = std::make_unique<GameObject>("Player2");
    player2->AddComponent<TransformComponent>(Vector2{800.0f, 0.0f});
    player2->AddComponent<RectRenderComponent>(Vector2{15.0f, 50.0f}, SDL_Color{255, 255, 255, 255});
    player2->AddComponent<ColliderComponent>(Vector2{15.0f, 50.0f});
    auto* controller2 = player2->AddComponent<PlayerControllerComponent2>(500.0f, false, true);
    controller2->BallTransform(ballTransform);
    auto* vidas2 = player2->AddComponent<VidasComponent>(7, LadoCampo::Derecha);
    vidas2->BallTransform(ballTransform);
    vidas2->PosicionarBarras(Vector2{800.0f, 20.0f});
    m_player2 = player2.get();
    m_entities.push_back(std::move(player2));

}

void GameScene::HandleEvent(const SDL_Event &event)
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

            case SDLK_A:
           
            if (m_player2) 
            {
                if (auto *manual = m_player2->GetComponent<PlayerControllerComponent2>())
                {
                    manual->Activar = !manual->Activar; 
                   
                }
            }
            break;

            default:
                break;
        }
    }
}

void GameScene::Update(float dt)
{
    auto* vidas1 = m_player1 ? m_player1->GetComponent<VidasComponent>() : nullptr;
    auto* vidas2 = m_player2 ? m_player2->GetComponent<VidasComponent>() : nullptr;

    if (vidas1 && vidas1->Vidas_Actual <= 0)
    {
        SDL_Log("Gana Player 2");
        if (m_manager)
        {
            m_manager->PushScene(std::make_unique<GameOverScene>(m_manager));
        }
    }
  
    else if (vidas2 && vidas2->Vidas_Actual <= 0)
    {
        SDL_Log("Gana Player 1");
        if (m_manager)
        {
            m_manager->PushScene(std::make_unique<GameOverScene>(m_manager));
        }
    }
    Scene::Update(dt);
}
void GameScene::FixedUpdate(float Fixed_dt)
{
    Scene::FixedUpdate(Fixed_dt);
    m_collisionManager.CheckCollisions();

}

void GameScene::Render(SDL_Renderer *renderer)
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
