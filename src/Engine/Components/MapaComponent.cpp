#include "Engine/Camera2D.hpp" 
#include "Engine/Components/MapaComponent.hpp" 


MapaComponent::MapaComponent(float mapaAncho, float mapaAlto, float pisoAncho, float pisoAlto)
    : MapaAncho(mapaAncho), MapaAlto(mapaAlto), PisoAncho(pisoAncho), PisoAlto(pisoAlto)
{
}
void MapaComponent::SetPisoTextura(SDL_Texture* texture)
{
    m_Texture = texture;
}
void MapaComponent::Render(SDL_Renderer* renderer)

{


    if (!renderer || !m_Texture){ return;}

    auto* camera = Camera2D::GetMain();



    for (float x = 0.0f; x < MapaAncho; x += PisoAncho)
    {
        for (float y = 0.0f; y < MapaAlto; y += PisoAlto)
        {

            SDL_FRect worldRect{ x, y, PisoAncho, PisoAlto };


            SDL_FRect screenRect = worldRect;
            if (camera)
            {

                if (!camera->IsVisible(worldRect))
                {
                    continue; 
                }


                screenRect = camera->ApplyToRect(worldRect);
            }

            SDL_RenderTexture(renderer, m_Texture, nullptr, &screenRect);
        }
    }
}
