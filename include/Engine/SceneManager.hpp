#pragma once

#include <memory>
#include <vector>
#include <SDL3/SDL.h>

class Scene; 

class SceneManager
{
public:
    enum class SceneAction {
        None,
        Change,
        Push,
        Pop,
        Clear
    };

    SceneManager() = default;
    ~SceneManager() = default;

    
    void ChangeScene(std::unique_ptr<Scene> new_scene);
    void PushScene(std::unique_ptr<Scene> new_scene);
    void PopScene();
    void Clear();
    bool HasScenes() const;
    void HandleEvent(const SDL_Event &event);
    void Update(float dt);
    void FixedUpdate(float Fixed_dt);
    void Render(SDL_Renderer *renderer);
    void ProcessPendingChanges();

private:
    std::vector<std::unique_ptr<Scene>> m_scenes;
    SceneAction m_pendingAction{SceneAction::None};
    std::unique_ptr<Scene> m_pendingScene{nullptr};

};
