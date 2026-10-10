#include "Engine/SceneManager.hpp"
#include "Engine/Scene.hpp"

void SceneManager::ChangeScene(std::unique_ptr<Scene> new_scene)
{
    m_pendingAction = SceneAction::Change;
    m_pendingScene = std::move(new_scene);
}

void SceneManager::PushScene(std::unique_ptr<Scene> new_scene)
{
    m_pendingAction = SceneAction::Push;
    m_pendingScene = std::move(new_scene);
}

void SceneManager::PopScene()
{
    m_pendingAction = SceneAction::Pop;
}

void SceneManager::Clear()
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

bool SceneManager::HasScenes() const
{
    return !m_scenes.empty();
}

void SceneManager::HandleEvent(const SDL_Event &event)
{
    if (!m_scenes.empty() && m_scenes.back())
    {
        m_scenes.back()->HandleEvent(event);
    }
}
void SceneManager::FixedUpdate(float dt)
{
    if (!m_scenes.empty() && m_scenes.back())
    {
        m_scenes.back()->FixedUpdate(dt);
    }

    ProcessPendingChanges();
}
void SceneManager::Update(float dt)
{
    if (!m_scenes.empty() && m_scenes.back())
    {
        m_scenes.back()->Update(dt);
    }

    ProcessPendingChanges();
}

void SceneManager::Render(SDL_Renderer *renderer)
{
    if (!m_scenes.empty() && m_scenes.back())
    {
        m_scenes.back()->Render(renderer);
    }
}

void SceneManager::ProcessPendingChanges()
{
    if (m_pendingAction == SceneAction::None) return;

    switch (m_pendingAction)
    {
        case SceneAction::Change:
            if (!m_scenes.empty())
            {
                if (m_scenes.back())
                {
                    m_scenes.back()->Exit();
                }
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
                if (m_scenes.back())
                {
                    m_scenes.back()->Exit();
                }
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
