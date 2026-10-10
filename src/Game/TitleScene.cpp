#include "Game/TitleScene.hpp"
#include <memory>
#include <SDL3/SDL.h>

#include "Engine/SceneManager.hpp"
#include "Game/GameScene.hpp"

TitleScene::TitleScene(SceneManager *manager)
    : Scene(manager, "TitleScene")
{
}

void TitleScene::HandleEvent(const SDL_Event &event)
{
    if (event.type == SDL_EVENT_KEY_DOWN)
    {
        if (event.key.key == SDLK_SPACE || event.key.key == SDLK_RETURN)
        {
            if (m_manager)
            {
                m_manager->ChangeScene(std::make_unique<GameScene>(m_manager));
            }
        }
    }
}

void TitleScene::Render(SDL_Renderer *renderer)
{
    if (!renderer) return;

    constexpr float SCREEN_WIDTH  = 960.0f;
    constexpr float SCREEN_HEIGHT = 540.0f;

    SDL_SetRenderDrawColor(renderer, 20, 25, 45, 255);
    SDL_RenderClear(renderer);

    constexpr float TITLE_WIDTH  = 400.0f;
    constexpr float TITLE_HEIGHT = 110.0f;

    SDL_FRect titleRect{
        (SCREEN_WIDTH - TITLE_WIDTH) / 2.0f,
        (SCREEN_HEIGHT - TITLE_HEIGHT) / 3.0f,
        TITLE_WIDTH,
        TITLE_HEIGHT
    };

    SDL_SetRenderDrawColor(renderer, 80, 100, 200, 255);
    SDL_RenderFillRect(renderer, &titleRect);

    constexpr float BUTTON_WIDTH  = 260.0f;
    constexpr float BUTTON_HEIGHT = 50.0f;

    SDL_FRect buttonRect{
        (SCREEN_WIDTH - BUTTON_WIDTH) / 2.0f,
        SCREEN_HEIGHT - 120.0f,
        BUTTON_WIDTH,
        BUTTON_HEIGHT
    };

    SDL_SetRenderDrawColor(renderer, 50, 200, 120, 255);
    SDL_RenderFillRect(renderer, &buttonRect);
}
