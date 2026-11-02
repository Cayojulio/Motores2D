#include "Game/GameScene.hpp"
#include <memory>
#include <SDL3/SDL.h>

#include "Engine/SceneManager.hpp"
#include "Engine/Components/VidasComponent.hpp"
#include "Engine/Components/MapaComponent.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Components/RectRenderComponent.hpp"
#include "Engine/Components/PlayerControllerComponent.hpp"
#include "Physics/ColliderComponent.hpp"
#include "Physics/PatrolComponent.hpp"
#include "Physics/BallComponent.hpp"
#include "Engine/ResourceManager.hpp"
#include "Game/PauseScene.hpp"
#include "Engine/Components/SpriteComponent.hpp"
#include "Game/GameOverScene.hpp"
#include "Engine/Components/PlayerControllerComponent2.hpp"

GameScene::GameScene(SceneManager *manager)
    : Scene(manager, "GameScene"),
      m_collisionManager(&m_entities)
{
}

void GameScene::Init()
{
ResourceManager* rm = GetResourceManager();
    if (!rm)  return;
    auto* camera = Camera2D::GetMain();
    camera->SetViewportSize(960.0f,540.0f);
    camera->SetPosition(Vector2{0.0f,0.0f});
    Vector2 Inicio=Vector2{0.0f,0.0f};
    Vector2 Final=Vector2{2000.0f,2000.0f};
    int Ancho=Final.x-Inicio.x;
    int Largo=Final.y-Inicio.y;
    camera->SetBounds(Inicio,Final);
SDL_Log("Dimensiones del mundo, Ancho: %d, Largo: %d", Ancho, Largo);
    SDL_Texture* pelotita = rm->GetTexture("assets/pelotota.png");
     SDL_Texture* Caminata = rm->GetTexture("assets/walk.png");
     SDL_Texture* Rectangulo = rm->GetTexture("assets/rectangulo.png");   
     SDL_Texture* Piso = rm->GetTexture("assets/Piso.png");     

    m_entities.clear();
    m_collisionManager.SetEntities(&m_entities);



    auto piso = std::make_unique<GameObject>("Piso");
    auto* PisoComp  = piso->AddComponent<MapaComponent>(2000,2000,32,32);
        auto* spritePiso = piso->AddComponent<SpriteComponent>(Piso);
            if (spritePiso)
    {
        spritePiso->Size(1.0f,1.0f); 
        spritePiso->SetLayer(0);
           SDL_Log("Si cargo %s", SDL_GetError());
    }
 if (PisoComp)
    {
           PisoComp->SetPisoTextura(Piso);
           SDL_Log("Si cargo PISO%s", SDL_GetError());
    }
    m_entities.push_back(std::move(piso));
// Pelota
    auto pelota = std::make_unique<GameObject>("Pelota");
    auto* ballTransform = pelota->AddComponent<TransformComponent>(Vector2{468.0f, 80.0f});

    pelota->AddComponent<ColliderComponent>(Vector2{15.0f, 15.0f});
    auto* ballcomponent = pelota->AddComponent<BallComponent>();
    auto* spriteComp = pelota->AddComponent<SpriteComponent>(pelotita);
    if (spriteComp)
    {
        spriteComp->Size(15.0f,15.0f); 
        spriteComp->SetLayer(1);
           SDL_Log("Si cargo %s", SDL_GetError());
    }
    m_entities.push_back(std::move(pelota));
//Player 1
    auto player = std::make_unique<GameObject>("Player");
    player->AddComponent<TransformComponent>(Vector2{100.0f, 0.0f});
    player->AddComponent<PlayerControllerComponent>(500.0f, false);
    player->AddComponent<ColliderComponent>(Vector2{15.0f, 50.0f});
    auto* vidas1 = player->AddComponent<VidasComponent>(5, LadoCampo::Izquierda);
    vidas1->BallTransform(ballTransform);
    vidas1->PosicionarBarras(Vector2{30.0f, 20.0f});
        auto* spriteComp2 = player->AddComponent<SpriteComponent>(Caminata);
    if (spriteComp2)
    {
        spriteComp2->Size(15.0f,50.0f); 
        spriteComp2->SetLayer(1);
           SDL_Log("Si cargo %s", SDL_GetError());
    }
auto* animComp = player->AddComponent<AnimationComponent>();
animComp->AddClip("WALK", 0, 8, 0.08f, true, 0);
    m_player1 = player.get();
    m_entities.push_back(std::move(player));


// Player2
    auto player2 = std::make_unique<GameObject>("Player2");
    player2->AddComponent<TransformComponent>(Vector2{800.0f, 0.0f});

    player2->AddComponent<ColliderComponent>(Vector2{15.0f, 50.0f});
    auto* controller2 = player2->AddComponent<PlayerControllerComponent2>(500.0f, false, true);
    controller2->BallTransform(ballTransform);
    controller2->BallComponent1(ballcomponent);
    auto* vidas2 = player2->AddComponent<VidasComponent>(5, LadoCampo::Derecha);
    vidas2->BallTransform(ballTransform);
    vidas2->PosicionarBarras(Vector2{800.0f, 20.0f});
        auto* spriteComp3 = player2->AddComponent<SpriteComponent>(Rectangulo);
    if (spriteComp3)
    {
        spriteComp3->Size(15.0f,50.0f); 
        spriteComp3->SetLayer(1);
           SDL_Log("Si cargo %s", SDL_GetError());
    }
    m_player2 = player2.get();
    m_entities.push_back(std::move(player2));
    camera->CenterOn(Vector2{480.0f, 270.0f});


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
        m_player1=nullptr;
            m_manager->PushScene(std::make_unique<GameOverScene>(m_manager));
        }
    }
  
    else if (vidas2 && vidas2->Vidas_Actual <= 0)
    {
        SDL_Log("Gana Player 1");
        if (m_manager)
        {
        m_player1=nullptr;
            m_manager->PushScene(std::make_unique<GameOverScene>(m_manager));
        }
    }
    if (m_player1)
    {
        auto* transform = m_player1->GetComponent<TransformComponent>();
        if (transform)
        {
           auto* camera = Camera2D::GetMain();

            camera->Follow(transform->position,12.0f, dt);
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
