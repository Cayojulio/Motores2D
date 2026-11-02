#include "Engine/Components/SpriteComponent.hpp"
#include <SDL3_image/SDL_image.h>
#include "Engine/GameObject.hpp"      
#include "Engine/Components/TransformComponent.hpp"

void SpriteComponent::Render(SDL_Renderer *renderer)
{
    if (!renderer || !m_texture)
    {
        return;
    }

    SDL_FRect dstRect{0.0f, 0.0f, m_width, m_height};
    double rotation = 0.0;

    if (owner)
    {
        auto *transform = owner->GetComponent<TransformComponent>();
        if (transform)
        {
            dstRect.x = transform->position.x;
            dstRect.y = transform->position.y;
            dstRect.w = (m_useSrcRect ? m_srcRect.w : m_width) * transform->scale.x;
            dstRect.h = (m_useSrcRect ? m_srcRect.h : m_height) * transform->scale.y;

            if (m_affectedByCamera)
            {
            auto *camera = Camera2D::GetMain(); 
            if (camera)
            {
            if (m_parallaxFactor.x > 0.0f || m_parallaxFactor.y > 0.0f)
            {
            if (!camera->IsVisible(dstRect))
                        {
            return; 
            }
                }

 dstRect = camera->ApplyToRect(dstRect, m_parallaxFactor);
            }
            }
            }
           }

    const SDL_FRect *src = m_useSrcRect ? &m_srcRect : nullptr;
    
    SDL_RenderTextureRotated(renderer, m_texture, src, &dstRect, rotation, nullptr, SDL_FLIP_NONE);

    // Restaurar modulaciones por defecto
    SDL_SetTextureColorMod(m_texture, 255, 255, 255);
    SDL_SetTextureAlphaMod(m_texture, 255);
}

void SpriteComponent::SetSrcRect(const SDL_FRect &rect)
{
    m_srcRect = rect;
    m_useSrcRect = true;
}

void SpriteComponent::SetUseSrcRect(bool use)
{
    m_useSrcRect = use;
}
