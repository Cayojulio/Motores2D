#include "Game/PauseScene.hpp"
#include <SDL3/SDL.h>
#include "Engine/SceneManager.hpp"

PauseScene::PauseScene(SceneManager *manager)
    : Scene(manager, "PauseScene")
{
}

void PauseScene::HandleEvent(const SDL_Event &event)
{
    if (event.type == SDL_EVENT_KEY_DOWN)
    {
        if (event.key.key == SDLK_ESCAPE || event.key.key == SDLK_P)
        {
            if (m_manager)
            {
                m_manager->PopScene();
            }
        }
    }
}

void PauseScene::Render(SDL_Renderer *renderer)
{
    if (!renderer) return;

    constexpr float SCREEN_WIDTH  = 960.0f;
    constexpr float SCREEN_HEIGHT = 540.0f;

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 175);
    SDL_FRect screen_overlay{0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderFillRect(renderer, &screen_overlay);

    constexpr float BOX_WIDTH  = 220.0f;
    constexpr float BOX_HEIGHT = 180.0f;

    float boxX = (SCREEN_WIDTH - BOX_WIDTH) / 2.0f;
    float boxY = (SCREEN_HEIGHT - BOX_HEIGHT) / 2.0f;

    SDL_FRect boxRect{boxX, boxY, BOX_WIDTH, BOX_HEIGHT};

    SDL_SetRenderDrawColor(renderer, 30, 30, 40, 240);
    SDL_RenderFillRect(renderer, &boxRect);

    SDL_SetRenderDrawColor(renderer, 240, 200, 60, 255);
    SDL_RenderRect(renderer, &boxRect);

    constexpr float BAR_WIDTH  = 20.0f;
    constexpr float BAR_HEIGHT = 70.0f;
    constexpr float BAR_GAP    = 20.0f;

    float totalIconWidth = (BAR_WIDTH * 2.0f) + BAR_GAP;
    float iconStartX     = boxX + (BOX_WIDTH - totalIconWidth) / 2.0f;
    float iconStartY     = boxY + (BOX_HEIGHT - BAR_HEIGHT) / 2.0f;

    SDL_FRect leftBar{iconStartX, iconStartY, BAR_WIDTH, BAR_HEIGHT};
    SDL_FRect rightBar{iconStartX + BAR_WIDTH + BAR_GAP, iconStartY, BAR_WIDTH, BAR_HEIGHT};

    SDL_SetRenderDrawColor(renderer, 240, 200, 60, 255);
    SDL_RenderFillRect(renderer, &leftBar);
    SDL_RenderFillRect(renderer, &rightBar);
}
