cmake_minimum_required(VERSION 3.16)
project(practica06 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# AddressSanitizer para detección de fugas y corrupción de memoria 
option(ENABLE_ASAN = 0N)
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
# Localizar SDL3
find_package(SDL3 QUIET)
if(NOT SDL3_FOUND)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL3 REQUIRED IMPORTED_TARGET sdl3)
set(SDL3_TARGET PkgConfig::SDL3)
else()

set(SDL3_TARGET SDL3::SDL3)
endif()
# Localizar SDL3_image
find_package(SDL3_image QUIET)
if(NOT SDL3_image_FOUND)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL3_IMAGE REQUIRED IMPORTED_TARGET sdl3-image)
set(SDL3_IMAGE_TARGET PkgConfig::SDL3_IMAGE)
else()
set(SDL3_IMAGE_TARGET SDL3_image::SDL3_image)
endif()
# Declaración del ejecutable con todos los componentes del motor
add_executable(${PROJECT_NAME}
src/main.cpp
src/Math/Vector2.cpp
src/Engine/GameObject.cpp
src/Engine/ResourceManager.cpp
src/Engine/Components/TransformComponent.cpp
src/Engine/Components/RectRenderComponent.cpp
src/Engine/Components/SpriteComponent.cpp
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
src/Engine/Components/PlayerControllerComponent2.cpp
src/Engine/Components/PlayerControllerComponent.cpp
src/Engine/Components/VidasComponent.cpp
src/Engine/Components/BotonComponent.cpp
include/Math/Vector2.hpp
include/Engine/Components/VidasComponent.hpp
include/Engine/Components/TransformComponent.hpp
include/Engine/Component.hpp
include/Engine/ResourceManager.hpp
include/Engine/GameObject.hpp
include/Engine/Components/RectRenderComponent.hpp
include/Engine/SceneManager.hpp
include/Engine/Scene.hpp
include/Engine/Components/PlayerControllerComponent.hpp
include/Physics/BallComponent.hpp
include/Physics/PatrolComponent.hpp
include/Physics/ColliderComponent.hpp
include/Physics/CollisionManager.hpp
include/Game/GameOverScene.hpp
include/Game/TitleScene.hpp
include/Game/GameScene.hpp
include/Game/PauseScene.hpp
include/Engine/Components/PlayerControllerComponent2.hpp
include/Engine/Components/SpriteComponent.hpp
include/Engine/Components/BotonComponent.hpp
)
target_include_directories(${PROJECT_NAME} PRIVATE include src)
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL3_TARGET} ${SDL3_IMAGE_TARGET})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION
${CMAKE_CURRENT_BINARY_DIR})
