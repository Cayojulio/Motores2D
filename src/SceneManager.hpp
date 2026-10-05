#pragma once

#include <memory>
#include <vector>
#include <SDL3/SDL.h>
#include "Scene.hpp"

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
    bool HasScenes() const { return !m_scenes.empty(); }

    SceneManager() = default;
    ~SceneManager() = default;


    void ChangeScene(std::unique_ptr<Scene> new_scene)
    {
        m_pendingAction = SceneAction::Change;
        m_pendingScene = std::move(new_scene);
    }

    void PushScene(std::unique_ptr<Scene> new_scene)
    {
        m_pendingAction = SceneAction::Push;
        m_pendingScene = std::move(new_scene);
    }

    void PopScene()
    {
        m_pendingAction = SceneAction::Pop;
    }

    void Clear()
    {
        while (!m_scenes.empty())
        {
            if (m_scenes.back())
            {
                m_scenes.back()->Exit();
            }
            m_scenes.pop_back();
        }
    }

    void HandleEvent(const SDL_Event &event)
    {
        if (!m_scenes.empty())
        {
            m_scenes.back()->HandleEvent(event);
        }
    }

    void Update(float dt)
    {
        if (!m_scenes.empty())
        {
            m_scenes.back()->Update(dt);
        }

        ProcessPendingChanges();
    }

    void Render(SDL_Renderer *renderer)
    {
        if (!m_scenes.empty())
        {
            m_scenes.back()->Render(renderer);
        }
    }

    std::vector<std::unique_ptr<Scene>> m_scenes;
    SceneAction m_pendingAction{SceneAction::None};
    std::unique_ptr<Scene> m_pendingScene{nullptr};
    void ProcessPendingChanges()
    {
        if (m_pendingAction == SceneAction::None) return;

        switch (m_pendingAction)
        {
            case SceneAction::Change:
                if (!m_scenes.empty())
                {
                    m_scenes.back()->Exit();
                    m_scenes.pop_back();
                }
                if (m_pendingScene)
                {
                    m_scenes.push_back(std::move(m_pendingScene));
                    m_scenes.back()->Init();
                }
                break;

            case SceneAction::Push:
                if (m_pendingScene)
                {
                    m_scenes.push_back(std::move(m_pendingScene));
                    m_scenes.back()->Init();
                }
                break;

            case SceneAction::Pop:
                if (!m_scenes.empty())
                {
                    m_scenes.back()->Exit();
                    m_scenes.pop_back();
                }
                break;

            case SceneAction::Clear:
                Clear();
                break;

            default:
                break;
        }

        m_pendingAction = SceneAction::None;
        m_pendingScene.reset();
    }

};
