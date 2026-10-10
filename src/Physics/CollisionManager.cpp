#include "Physics/CollisionManager.hpp"
#include "Engine/GameObject.hpp"
#include "Physics/ColliderComponent.hpp"

CollisionManager::CollisionManager(const std::vector<std::unique_ptr<GameObject>> *entities)
    : m_entities(entities)
{
}

void CollisionManager::SetEntities(const std::vector<std::unique_ptr<GameObject>> *entities)
{
    m_entities = entities;
}

bool CollisionManager::CheckAABB(const SDL_FRect &a, const SDL_FRect &b)
{
    bool overlapX = (a.x + a.w > b.x) && (a.x < b.x + b.w);
    bool overlapY = (a.y + a.h > b.y) && (a.y < b.y + b.h);

    return overlapX && overlapY;
}

bool CollisionManager::CheckCollision(const ColliderComponent &a, const ColliderComponent &b)
{
    SDL_FRect boundsA = a.GetWorldBounds();
    SDL_FRect boundsB = b.GetWorldBounds();
    return CheckAABB(boundsA, boundsB);
}

void CollisionManager::CheckCollisions()
{
    if (m_entities == nullptr) return;

    // Reiniciar estados de colisión
    for (const auto &entity : *m_entities)
    {
        if (entity != nullptr)
        {
            auto *collider = entity->GetComponent<ColliderComponent>();
            if (collider != nullptr)
            {
                collider->is_colliding = false;
            }
        }
    }

    // Comprobar parejas de entidades
    size_t count = m_entities->size();
    for (size_t i = 0; i < count; ++i)
    {
        auto *entityA = (*m_entities)[i].get();
        if (entityA == nullptr) continue;

        auto *colliderA = entityA->GetComponent<ColliderComponent>();
        if (colliderA == nullptr) continue;

        for (size_t j = i + 1; j < count; ++j)
        {
            auto *entityB = (*m_entities)[j].get();
            if (entityB == nullptr) continue;

            auto *colliderB = entityB->GetComponent<ColliderComponent>();
            if (colliderB == nullptr) continue;

            if (CheckCollision(*colliderA, *colliderB))
            {
                colliderA->is_colliding = true;
                colliderB->is_colliding = true;

                entityA->OnCollision(entityB);
                entityB->OnCollision(entityA);
            }
        }
    }
}
