#pragma once

#include "Engine/General/Core/GameEngine.hpp"
#include "Engine/Renderer/Mesh/Mesh.hpp"
#include "Engine/Renderer/Material/Material.hpp"
#include "Engine/Renderer/Mesh/MeshRenderer.hpp"
#include "Game/GameCommon.hpp"
#include "Game/TheApp.hpp"
#include "Game/TheCamera.hpp"
#include "Game/Sphere.hpp"
#include "Game/Cube.hpp"
#include "Game/LightSystem.hpp"
#include "Engine/Renderer/Framebuffer.hpp"
#include "Game/MaterialManager.hpp"


class TheGame;
extern TheGame* g_theGame;

class TheGame {
public:
	//STRUCTORS AND INITIALIZATION
	TheGame();
	~TheGame();

	void RenderInitialization();

	//UPDATE
	void Update(float deltaSeconds);

	void UpdateMaterials() const;

	//RENDER
	void SetUpPerspectiveProjection() const;
	void Render() const;

	//USER INPUT
	void HandlePlayerLook();
	void HandlePlayerMovement(float deltaSeconds);

	//OTHER
	void RegisterCommands();

private:
	std::vector<Cube> m_cubes;

	Framebuffer* m_fbo;
};

//CONSOLE COMMANDS
void Add(Command& args);