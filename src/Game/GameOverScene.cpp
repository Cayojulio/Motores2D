#include "Game/GameOverScene.hpp"
#include <memory>
#include "Engine/SceneManager.hpp"
#include "Game/GameScene.hpp"
#include "Game/TitleScene.hpp"

GameOverScene::GameOverScene(SceneManager *manager)
    : Scene(manager, "GameOverScene")
{
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

    constexpr float SCREEN_WIDTH  = 960.0f;
    constexpr float SCREEN_HEIGHT = 540.0f;

    SDL_SetRenderDrawColor(renderer, 45, 15, 20, 255);
    SDL_RenderClear(renderer);

    constexpr float PANEL_WIDTH  = 400.0f;
    constexpr float PANEL_HEIGHT = 200.0f;

    float panelX = (SCREEN_WIDTH - PANEL_WIDTH) / 2.0f;
    float panelY = (SCREEN_HEIGHT - PANEL_HEIGHT) / 2.0f;

    SDL_FRect panelRect{panelX, panelY, PANEL_WIDTH, PANEL_HEIGHT};

    SDL_SetRenderDrawColor(renderer, 20, 10, 15, 255);
    SDL_RenderFillRect(renderer, &panelRect);

    SDL_SetRenderDrawColor(renderer, 220, 50, 50, 255);
    SDL_RenderRect(renderer, &panelRect);

    constexpr float DECO_BAR_W = 120.0f;
    constexpr float DECO_BAR_H = 10.0f;

    SDL_FRect decoBar{
        panelX + (PANEL_WIDTH - DECO_BAR_W) / 2.0f,
        panelY + 40.0f,
        DECO_BAR_W,
        DECO_BAR_H
    };

    SDL_SetRenderDrawColor(renderer, 220, 50, 50, 255);
    SDL_RenderFillRect(renderer, &decoBar);
}
