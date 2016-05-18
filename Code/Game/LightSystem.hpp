#pragma once

#define _USE_MATH_DEFINES

#include "Engine/General.hpp"
#include "Engine/Renderer/Light3D.hpp"

class LightSystem;
extern LightSystem* g_theLightSystem;

class LightSystem {
public:
	LightSystem();

	void Update(float deltaSeconds);
	void Render() const;

	std::vector<Light3D> GetLights() const;

private:
	std::vector<Light3D> m_lights;

	float m_age;
};