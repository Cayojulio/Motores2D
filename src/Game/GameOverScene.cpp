#include "Game/GameOverScene.hpp"
#include <memory>
#include "Game/TitleScene.hpp"
#include "Engine/ResourceManager.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/Components/TransformComponent.hpp"
#include "Engine/Components/BotonComponent.hpp"
#include "Game/GameScene.hpp"
GameOverScene::GameOverScene(SceneManager *manager)
    : Scene(manager, "GameOverScene")
{
}
void GameOverScene::Init()
{
ResourceManager* rm = GetResourceManager();
    if (!rm)  return;
    auto* camera = Camera2D::GetMain();

    SDL_Texture* Game = rm->GetTexture("assets/Game.jpeg");
    camera->SetViewportSize(960.0f,540.0f);
    camera->SetPosition(Vector2{480.0f, 270.0f});
constexpr float IMG_WIDTH  = 300.0f;
constexpr float IMG_HEIGHT = 80.0f;
float posX = (960.0f - IMG_WIDTH) / 2.0f;
float posY = (540.0f - IMG_HEIGHT) / 2.0f;

auto gameOverObj = std::make_unique<GameObject>("GameOverImage");
auto* transform = gameOverObj->AddComponent<TransformComponent>(Vector2{posX, posY});
auto* sprite = gameOverObj->AddComponent<SpriteComponent>(Game);

if (sprite)
{
    sprite->Size(IMG_WIDTH, IMG_HEIGHT); 
}

m_entities.push_back(std::move(gameOverObj));
 camera->CenterOn(Vector2{480.0f, 270.0f});
    }

void GameOverScene::HandleEvent(const SDL_Event &event)
{
    if (event.type == SDL_EVENT_KEY_DOWN)
    {
        if (event.key.key == SDLK_R || event.key.scancode == SDL_SCANCODE_R)
        {
            if (m_manager)
            {
                m_manager->ChangeScene(std::make_unique<GameScene>(m_manager));
            }
        }
        else if (event.key.key == SDLK_M || event.key.scancode == SDL_SCANCODE_M ||
                 event.key.key == SDLK_ESCAPE || event.key.scancode == SDL_SCANCODE_ESCAPE)
        {
            if (m_manager)
            {
                m_manager->ChangeScene(std::make_unique<TitleScene>(m_manager));
            }
        }
    }
}

void GameOverScene::Render(SDL_Renderer *renderer)
{
    if (!renderer) return;
Scene::Render(renderer);
}
