#pragma once

#include "Engine/Scene.hpp"

class SceneManager;
class GameScene;

class TitleScene : public Scene
{
public:
    explicit TitleScene(SceneManager *manager);

void HandleEvent(const SDL_Event &event) override;
void Render(SDL_Renderer *renderer) override;
};
