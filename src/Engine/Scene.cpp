#include "Engine/Scene.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/GameObject.hpp"

Scene::Scene(SceneManager *manager, std::string name)
    : m_manager(manager), m_name(std::move(name))
{
}

void Scene::Init() 
{
}

void Scene::Exit() 
{
}

void Scene::HandleEvent(const SDL_Event &event) 
{
}

void Scene::Update(float dt)
{
    for (auto &entity : m_entities)
    {
        if (entity && entity->IsActive())
        {
            entity->Update(dt);
        }
    }
}
void Scene::FixedUpdate(float fixed_dt)
{
    for (auto &entity : m_entities)
    {
        if (entity && entity->IsActive())
        {
            entity->FixedUpdate(fixed_dt);
        }
    }
}


void Scene::Render(SDL_Renderer *renderer)
{
    for (auto &entity : m_entities)
    {
        if (entity && entity->IsActive())
        {
            entity->Render(renderer);
        }
    }
}
