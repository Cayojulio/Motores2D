#pragma once

#include <memory>
#include <vector>
#include <SDL3/SDL.h>
#include "Math/Vector2.hpp"
#include "Engine/TransformComponent.hpp"
enum class LadoCampo 
{ 
    Izquierda, 
    Derecha 
};
class VidasComponent : public Component
{
public:
int Vidas_Totales{3};        
int Vidas_Actual{3};   
Vector2 bar_size{20.0f, 8.0f}; 
float spacing{10.0f};         
LadoCampo ladoDefendido{LadoCampo::Izquierda};
TransformComponent* m_ballTransform{nullptr};
Vector2 posicion{20.0f, 20.0f}; 
SDL_Color color{255, 50, 50, 255};
void PosicionarBarras(Vector2 pos)
{
 posicion = pos
;}
explicit VidasComponent(int vidas, LadoCampo lado = LadoCampo::Izquierda);
void BallTransform(TransformComponent* ballTransform) 
{ 
m_ballTransform = ballTransform
;}
void Daño();
void Reset();
void Update(float dt) override;
void Render(SDL_Renderer* renderer);
};
