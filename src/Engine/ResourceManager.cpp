#include "Engine/ResourceManager.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
ResourceManager::~ResourceManager() = default;

SDL_Texture* ResourceManager::GetTexture(const std::string &filepath)
{
    auto it = m_textures.find(filepath);
    if (it != m_textures.end())
    {
        return it->second.get();
    }
    if (!m_renderer)
    {
    SDL_Log("¡ERROR! ResourceManager no tiene un renderer asignado.");
        return nullptr;
    }

    SDL_Surface *surface = IMG_Load(filepath.c_str());
    if (!surface)
    {
    SDL_Log("¡ERROR! No se pudo cargar la imagen %s: %s", filepath.c_str(), SDL_GetError());
        return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_DestroySurface(surface);
    if (!texture)
    {
    SDL_Log("¡ERROR! No se pudo crear la textura: %s", SDL_GetError());
        return nullptr;
    }
    m_textures[filepath] = TexturePtr(texture);
    return m_textures[filepath].get();
}
    
   





