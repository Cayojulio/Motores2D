#pragma once

#include <SDL3/SDL.h>
#include "Engine/Component.hpp"
#include "Math/Vector2.hpp"
#include "Engine/Camera2D.hpp"
class SpriteComponent : public Component 
{
private:
    SDL_Texture *m_texture{nullptr};
    
    float m_width{0.0f};
    float m_height{0.0f};
    int m_layer{0}; // Capa de ordenamiento (Z-Order)
Vector2 m_parallaxFactor{1.0f, 1.0f}; // Sensibilidad almovimiento de la cámara
bool m_affectedByCamera{true}; // Falso para elementos estáticos de UI
    bool m_useSrcRect{false};
    SDL_FRect m_srcRect{0.0f, 0.0f, 0.0f, 0.0f};
    
    SDL_FColor m_colorMod{1.0f, 1.0f, 1.0f, 1.0f};
    SDL_FlipMode m_flip{SDL_FLIP_NONE};

public:
    SpriteComponent() = default;

    explicit SpriteComponent(SDL_Texture *texture) : m_texture(texture) {}
    
    ~SpriteComponent() = default;

    void Init() override 
    {
        
    }

  
    void Render(SDL_Renderer *renderer) override;


    void SetTexture(SDL_Texture *texture) { m_texture = texture; }
    SDL_Texture *GetTexture() const { return m_texture; }
void SetSrcRect(const SDL_FRect &rect);
    void SetUseSrcRect(bool use);
    void Size(float w, float h) { m_width = w; m_height = h; }
    void Color(float r, float g, float b, float a) { m_colorMod = {r, g, b, a}; }
float Ancho() const { return m_width; }
float Altura() const { return m_height; }
void SetLayer(int layer) { m_layer = layer; }
int GetLayer() const { return m_layer; }
void SetParallaxFactor(const Vector2 &factor) { m_parallaxFactor = factor; }
const Vector2 &GetParallaxFactor() const { return m_parallaxFactor; }
void SetAffectedByCamera(bool affected) { m_affectedByCamera = affected;}
bool IsAffectedByCamera() const { return m_affectedByCamera; }


};
