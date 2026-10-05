#pragma once

#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <SDL3/SDL.h>
#include "GameObject.hpp"
#include "SceneManager.hpp"
class SceneManager;

class Scene
{
protected:
    SceneManager *m_manager{nullptr};
    std::vector<std::unique_ptr<GameObject>> m_entities;
    std::string m_name;

public:
    explicit Scene(SceneManager *manager, std::string name = "UnnamedScene")
        : m_manager(manager), m_name(std::move(name))
    {
    }

    virtual ~Scene() = default;

    // --- Gestión de Memoria (Sin copia) ---
    Scene(const Scene &) = delete;
    Scene &operator=(const Scene &) = delete;

    Scene(Scene &&) noexcept = default;
    Scene &operator=(Scene &&) noexcept = default;

    // --- Ciclo de Vida ---
    virtual void Init() {}
    virtual void Exit() {}
      
  virtual void HandleEvent(const SDL_Event &event) {}

    virtual void Update(float dt)
    {
        for (auto &entity : m_entities)
        {
            if (entity && entity->IsActive())
            {
                entity->Update(dt);
            }
        }
    }

    virtual void Render(SDL_Renderer *renderer)
    {
        for (auto &entity : m_entities)
        {
            if (entity && entity->IsActive())
            {
                entity->Render(renderer);
            }
        }
    }
   
   
  };
   
   
