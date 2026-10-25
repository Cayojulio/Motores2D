#pragma once

#include "Engine/Scene.hpp"
#include "Engine/ResourceManager.hpp"
#include "Engine/Components/SpriteComponent.hpp"
class SceneManager;
class GameScene;

class TitleScene : public Scene
{

public:
explicit TitleScene(SceneManager *manager);
    void Init() override;
        void Update(float dt) override;
void HandleEvent(const SDL_Event &event) override;
void Render(SDL_Renderer *renderer) override;
};
