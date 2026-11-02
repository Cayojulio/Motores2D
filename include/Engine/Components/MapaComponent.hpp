#pragma once

#include <memory>
#include <vector>
#include <SDL3/SDL.h>
#include "Math/Vector2.hpp"
#include "Engine/Components/TransformComponent.hpp"

class MapaComponent : public Component {


public:
float MapaAncho= 2000.0f;
float MapaAlto= 2000.0f;
float PisoAncho=32.0f;
float PisoAlto=32.0f;
SDL_Texture* m_Texture=nullptr;

explicit MapaComponent(float MapaAncho, float MapaAlto,float PisoAncho,float PisoAlto);
void SetPisoTextura(SDL_Texture* texture);
void Render(SDL_Renderer* renderer) override;
};
