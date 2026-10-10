#include "Engine/GameObject.hpp"

GameObject::GameObject(std::string tag)
    : m_tag(std::move(tag))
{
}

// Al definir el destructor aquí, unique_ptr<Component> puede ver la
// definición completa de Component sin causar incomplete type errors.
GameObject::~GameObject() = default;

void GameObject::Update(float dt)
{
    if (!m_active) return;

    for (auto &component : m_components)
    {
        if (component)
        {
            component->Update(dt);
        }
    }
}
void GameObject::FixedUpdate(float fixed_dt)
{
    if (!m_active) return;

    for (auto &component : m_components)
    {
        if (component)
        {
            component->FixedUpdate(fixed_dt); 
        }
    }
}

void GameObject::OnCollision(GameObject *other)
{
    if (!m_active) return;

    for (auto &component : m_components)
    {
        if (component)
        {
            component->OnCollision(other);
        }
    }
}

void GameObject::Render(SDL_Renderer *renderer)
{
    if (!m_active) return;

    for (auto &component : m_components)
    {
        if (component)
        {
            component->Render(renderer);
        }
    }
}
