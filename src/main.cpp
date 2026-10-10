#define SDL_MAIN_USE_CALLBACKS 1

#include <vector>
#include <memory>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "Math/Vector2.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/TransformComponent.hpp"
#include "Engine/RectRenderComponent.hpp"
#include "Engine/PlayerControllerComponent.hpp"
#include "Physics/PatrolComponent.hpp"
#include "Physics/ColliderComponent.hpp"
#include "Physics/CollisionManager.hpp"
#include "Physics/BallComponent.hpp"
#include "Engine/SceneManager.hpp"
#include "Game/TitleScene.hpp"
#include "Engine/Scene.hpp"
#include "Engine/SceneManager.hpp"

#include "Game/TitleScene.hpp"
#include "Game/GameScene.hpp"
#include "Game/GameOverScene.hpp"

void SDL_LogPlatformInfo();

struct AppState
{
SDL_Renderer *renderer{nullptr};
SDL_Window *window{nullptr};
Uint64 last_ticks{0};
// El SceneManager ahora gobierna el estado completo de la aplicación
SceneManager sceneManager;
} appstate;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
*appstate = &::appstate;
    // 1. Inicializar sub-sistemas de SDL3
        if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error al inicializar SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Sugerir a la plataforma una tasa objetivo de 60 FPS
    SDL_SetHint(SDL_HINT_MAIN_CALLBACK_RATE, "60");

    SDL_LogPlatformInfo();

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    if (!SDL_CreateWindowAndRenderer("Práctica 02 - Vect	ores y Movimiento", 960, 540, SDL_WINDOW_RESIZABLE, &window, &renderer))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error al crear ventana o renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_Log("Renderer Driver activo: %s", SDL_GetRendererName(renderer));

    ::appstate.window = window;
    ::appstate.renderer = renderer;
    ::appstate.last_ticks = SDL_GetTicks();
    ::appstate.sceneManager.ChangeScene(std::make_unique<TitleScene>(&::appstate.sceneManager));
    ::appstate.sceneManager.ProcessPendingChanges();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    AppState *app = static_cast<AppState *>(appstate);

    // Cálculo de Delta Time
    Uint64 current_ticks = SDL_GetTicks();
    float delta_time = static_cast<float>(current_ticks - app->last_ticks) / 1000.0f;
    app->last_ticks = current_ticks;

    // Evitar salto de tiempo excesivo (ej. al arrastrar la ventana)
    if (delta_time > 0.05f)
    {
        delta_time = 0.05f;
    }
    constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;
    // Actualización y cambio de escenas
    app->sceneManager.ProcessPendingChanges();
    app->sceneManager.Update(delta_time);
    app->sceneManager.FixedUpdate(FIXED_TIMESTEP);

    // Renderizado
    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255); // Fondo negro por defecto
    SDL_RenderClear(app->renderer);

    app->sceneManager.Render(app->renderer);

    SDL_RenderPresent(app->renderer);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    AppState *app = static_cast<AppState *>(appstate);

    if (event->type == SDL_EVENT_QUIT)
    {
        return SDL_APP_SUCCESS; // Permite cerrar la aplicación limpiamente
    }

    if (app && app->sceneManager.HasScenes())
    {
        app->sceneManager.HandleEvent(*event);
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
AppState *app = static_cast<AppState *>(appstate);
if (app)
{
SDL_DestroyRenderer(app->renderer);
SDL_DestroyWindow(app->window);
}
SDL_Quit();
}

void SDL_LogPlatformInfo()
{
    SDL_Log("Plataforma: %s", SDL_GetPlatform());
    SDL_Log("Cores lógicos de CPU: %d", SDL_GetNumLogicalCPUCores());
    SDL_Log("RAM total: %d MB", SDL_GetSystemRAM());
    SDL_Log("Driver de video: %s", SDL_GetCurrentVideoDriver());
}
