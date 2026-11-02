#include "Engine/Scene.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/Components/SpriteComponent.hpp"
#include <iostream>
Scene::Scene(SceneManager *manager, std::string name)
    : m_manager(manager), m_name(std::move(name))
{
}
ResourceManager* Scene::GetResourceManager() const
{
    if (m_manager)
    {
        return m_manager->GetResourceManager(); 
    }
    return nullptr;
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
std::vector<GameObject*> renderQueue;

    
    for (auto& entity : m_entities)
    {

        if (entity && entity->IsActive()) 
        {
            if (entity->HasComponent<SpriteComponent>()) 
            {
                renderQueue.push_back(entity.get());
            }
        }
    }
std::stable_sort(renderQueue.begin(), renderQueue.end(), [](const
GameObject *a, const GameObject *b) {
int layerA = 0;
int layerB = 0;
if (auto *spriteA = a->GetComponent<SpriteComponent>()) layerA =spriteA->GetLayer();
if (auto *spriteB = b->GetComponent<SpriteComponent>()) layerB =spriteB->GetLayer();
return layerA < layerB;
});
    for (auto &entity : renderQueue)
    {
            entity->Render(renderer);
      
    }




}
