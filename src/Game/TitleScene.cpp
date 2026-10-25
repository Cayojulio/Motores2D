#include "Game/TitleScene.hpp"
#include <memory>
#include <SDL3/SDL.h>
#include "Engine/ResourceManager.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Components/BotonComponent.hpp"
#include "Game/GameScene.hpp"

TitleScene::TitleScene(SceneManager *manager)
    : Scene(manager, "TitleScene")
{
}

  void TitleScene::Init()
{
ResourceManager* rm = GetResourceManager();
    if (!rm)  return;


    SDL_Texture* tituloImg = rm->GetTexture("assets/Titulo.png");
    SDL_Texture* Boton = rm->GetTexture("assets/botonxd.png");
    SDL_Texture* Fondo = rm->GetTexture("assets/Fondooo.png");
    if (!tituloImg)
{
    SDL_Log("¡ERROR! No se pudo cargar la textura: %s", SDL_GetError());
}
else
{
    SDL_Log("¡Textura cargada con éxito!");
}
    constexpr float SCREEN_WIDTH  = 960.0f;
    constexpr float SCREEN_HEIGHT = 540.0f;
    constexpr float TITLE_WIDTH   = 400.0f;
    constexpr float TITLE_HEIGHT  = 110.0f;
    constexpr float ANCHO_BOTON  = TITLE_WIDTH/2.0f;
    constexpr float LARGO_BOTON  = TITLE_HEIGHT/3.0f;
    float posX = (SCREEN_WIDTH - TITLE_WIDTH) / 2.0f;
    float posY = (SCREEN_HEIGHT - TITLE_HEIGHT) / 3.0f;
    float posbotonX = (SCREEN_WIDTH - ANCHO_BOTON) / 2.0f;
    float posbotonY = SCREEN_HEIGHT / 2.0f+100;
    auto Fondotit = std::make_unique<GameObject>("Fondotit");
    Fondotit->AddComponent<TransformComponent>(Vector2{0.0f, 0.0f});
    auto* spriteComp2 = Fondotit->AddComponent<SpriteComponent>(Fondo);
    if (spriteComp2)
    {
        spriteComp2->Size(SCREEN_WIDTH,SCREEN_HEIGHT); 
    }
    m_entities.push_back(std::move(Fondotit));
    auto tituloObj = std::make_unique<GameObject>("Titulo");
    tituloObj->AddComponent<TransformComponent>(Vector2{posX, posY});
    auto* spriteComp = tituloObj->AddComponent<SpriteComponent>(tituloImg);
    if (spriteComp)
    {
        spriteComp->Size(TITLE_WIDTH, TITLE_HEIGHT); 
    }
    m_entities.push_back(std::move(tituloObj));
    
    
    auto Play = std::make_unique<GameObject>("Play");
    Play->AddComponent<TransformComponent>(Vector2{posbotonX, posbotonY});
    auto* spriteComp1 = Play->AddComponent<SpriteComponent>(Boton);
    if (spriteComp1)
    {
        spriteComp1->Size(ANCHO_BOTON,LARGO_BOTON); 
    }
    Play->AddComponent<BotonComponent>();
    m_entities.push_back(std::move(Play));
    
    
    
    
}

void TitleScene::HandleEvent(const SDL_Event &event)
{


 if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            for (const auto& entity : m_entities)
            {
                auto* Boton = entity->GetComponent<BotonComponent>();
                if (Boton && Boton->EstaEncima())
                {
                    if (m_manager)
                    {
                        m_manager->ChangeScene(std::make_unique<GameScene>(m_manager));
                    }
                    break; 
                }
            }
        }
    }
}

void TitleScene::Update(float dt)
{
    Scene::Update(dt);
}

void TitleScene::Render(SDL_Renderer *renderer)
{
    if (!renderer) return;


    SDL_SetRenderDrawColor(renderer, 20, 25, 45, 255);
    SDL_RenderClear(renderer);

    Scene::Render(renderer);
}
