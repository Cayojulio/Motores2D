#pragma once

#include <vector>
#include <memory>
#include <SDL3/SDL.h>

class GameObject;
class ColliderComponent;

class CollisionManager
{
private:
    const std::vector<std::unique_ptr<GameObject>> *m_entities{nullptr};

public:
    CollisionManager() = default;
    explicit CollisionManager(const std::vector<std::unique_ptr<GameObject>> *entities);

    void SetEntities(const std::vector<std::unique_ptr<GameObject>> *entities);

    bool CheckAABB(const SDL_FRect &a, const SDL_FRect &b);
    bool CheckCollision(const ColliderComponent &a, const ColliderComponent &b);
    void CheckCollisions();
};
