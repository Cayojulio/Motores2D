cmake_minimum_required(VERSION 3.16)
project(practica04_motor LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# AddressSanitizer para detección de fugas y corrupción de memoria (opcional
option(ENABLE_ASAN "Habilitar AddressSanitizer (opcional/demostrativo)" ON)
if(ENABLE_ASAN)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang" AND NOT WIN32)
message(STATUS "AddressSanitizer (ASan) habilitado: -
fsanitize=address -g")
add_compile_options(-fsanitize=address -g -fno-omit-frame-pointer)
add_link_options(-fsanitize=address)
else()
message(WARNING "AddressSanitizer omitido: no compatible o
susceptible a problemas de enlazado en este entorno.")
endif()
endif()
# Localización de SDL3
find_package(SDL3 QUIET)
if(NOT SDL3_FOUND)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL3 REQUIRED IMPORTED_TARGET sdl3)
set(SDL3_TARGET PkgConfig::SDL3)
else()
set(SDL3_TARGET SDL3::SDL3)
endif()
# Declaración del ejecutable con todos los componentes del motor
add_executable(${PROJECT_NAME}
src/main.cpp
src/Math/Vector2.cpp
src/Engine/GameObject.cpp
src/Engine/TransformComponent.cpp
src/Engine/RectRenderComponent.cpp
src/Engine/Scene.cpp
src/Engine/SceneManager.cpp
src/Physics/ColliderComponent.cpp
src/Physics/CollisionManager.cpp
src/Physics/PatrolComponent.cpp
src/Physics/BallComponent.cpp
src/Game/GameOverScene.cpp
src/Game/TitleScene.cpp
src/Game/PauseScene.cpp
src/Game/GameScene.cpp
src/Engine/PlayerControllerComponent2.cpp
src/Engine/PlayerControllerComponent.cpp
src/Engine/VidasComponent.cpp
include/Math/Vector2.hpp
include/Engine/VidasComponent.hpp
include/Engine/TransformComponent.hpp
include/Engine/Component.hpp
include/Engine/GameObject.hpp
include/Engine/RectRenderComponent.hpp
include/Engine/SceneManager.hpp
include/Engine/Scene.hpp
include/Engine/PlayerControllerComponent.hpp
include/Physics/BallComponent.hpp
include/Physics/PatrolComponent.hpp
include/Physics/ColliderComponent.hpp
include/Physics/CollisionManager.hpp
include/Game/GameOverScene.hpp
include/Game/TitleScene.hpp
include/Game/GameScene.hpp
include/Game/PauseScene.hpp
include/Engine/PlayerControllerComponent2.hpp
)
target_include_directories(${PROJECT_NAME} PRIVATE
include
src
)
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL3_TARGET})

