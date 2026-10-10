#pragma once

#include "Engine/Scene.hpp"

class SceneManager;
class GameScene;
class TitleScene;

class GameOverScene : public Scene
{
public:
    explicit GameOverScene(SceneManager *manager);

    void HandleEvent(const SDL_Event &event) override;
    void Update(float deltaTime) override {}
    void Render(SDL_Renderer *renderer) override;
};
