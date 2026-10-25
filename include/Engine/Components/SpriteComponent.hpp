#pragma once

#include <SDL3/SDL.h>
#include "Engine/Component.hpp"

class SpriteComponent : public Component 
{
private:
    SDL_Texture *m_texture{nullptr};
    
    float m_width{0.0f};
    float m_height{0.0f};
    
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
    
    void Size(float w, float h) { m_width = w; m_height = h; }
    void Color(float r, float g, float b, float a) { m_colorMod = {r, g, b, a}; }
float Ancho() const { return m_width; }
float Altura() const { return m_height; }
};
