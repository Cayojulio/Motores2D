#include "Engine/Camera2D.hpp"
#include "Math/Vector2.hpp"
#include "Engine/GameObject.hpp"
Camera2D* Camera2D::s_mainCamera = nullptr;
Camera2D::Camera2D()
{
    if (s_mainCamera == nullptr)
    {
        s_mainCamera = this;
    }
}

Camera2D::~Camera2D()
{

    if (s_mainCamera == this)
    {
    s_mainCamera = nullptr;
    }
}


void Camera2D::SetPosition(const Vector2 &pos)
{
    m_position = pos;

    if (m_useBounds)
    {
    m_position.x = std::clamp(m_position.x, m_minBounds.x, m_maxBounds.x - m_viewportSize.x);
    m_position.y = std::clamp(m_position.y, m_minBounds.y, m_maxBounds.y - m_viewportSize.y);
    }
}

void Camera2D::CenterOn(const Vector2 &targetPos)
{
Vector2 targetPosCentrada = targetPos - (m_viewportSize * 0.5f);
SetPosition(targetPosCentrada);
}




void Camera2D::Follow(const Vector2 &targetPos, float smoothSpeed, float dt)
{

Vector2 targetPosCentrada = targetPos - (m_viewportSize * 0.5f);
Vector2 nuevaPos = Vector2::Lerp(m_position, targetPosCentrada, smoothSpeed * dt);
SetPosition(nuevaPos);
}

bool Camera2D::IsVisible(const SDL_FRect &worldRect) const
{

    float camLeft = m_position.x;
    float camRight = m_position.x + m_viewportSize.x;
    float camTop = m_position.y;
    float camBottom = m_position.y + m_viewportSize.y;

   
    if (worldRect.x + worldRect.w < camLeft || worldRect.x > camRight ||
        worldRect.y + worldRect.h < camTop || worldRect.y > camBottom)
    {
        return false; 
    }

    return true; 
}


SDL_FRect Camera2D::ApplyToRect(const SDL_FRect &worldRect, const Vector2 &parallaxFactor) const
{
SDL_FRect rect;
rect.x = worldRect.x - (m_position.x * parallaxFactor.x);
rect.y = worldRect.y - (m_position.y * parallaxFactor.y);
rect.w = worldRect.w;
rect.h = worldRect.h;
return rect;
}
