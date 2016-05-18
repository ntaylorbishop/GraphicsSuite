#include "Game/LightSystem.hpp"

LightSystem* g_theLightSystem = nullptr;

LightSystem::LightSystem() 
	: m_age(0.f)
{
	//m_lights.push_back(Light3D(Vector3(0.f, -3.f, 0.f), RGBA::WHITE, 10.f));
	//LOCAL POINT LIGHT
	m_lights.push_back(Light3D(Vector3(10.f, 10.f, 5.f), RGBA::GREEN, 8.f));

	//LOCAL CONE LIGHT
	m_lights.push_back(Light3D(Vector3(5.f, 5.f, 5.f)
		, Vector3(0.f, 0.f, -1.f)
		, RGBA::RED
		, 0.f, 10.f
		, 1.f, 0.f
		, 0.1f, 0.5f
		, 0.f, 4.f
	));

	//GLOBAL CONE LIGHT
	m_lights.push_back(Light3D(Vector3(5.f, 80.f, 80.f)
		, Vector3(0.f, -1.f, -1.f)
		, RGBA::WHITE
		, 0.f, 1.f
		, 0.3f, 0.3f
		, 0.1f, 0.5f
		, 0.f, 1.f
		));

	//GlOBAL POINT LIGHT
	m_lights.push_back(
		Light3D
			( Vector3(5.f, -80.f, 80.f)
			, Vector3(0.f, 0.f, -1.f)
			, RGBA::BLUE
			, 10.f, 15.f
			, 1.f, 1.f, 1.f
			, 1.f, -1.f
			, 1.f, 1.f
		)
	);
}

void LightSystem::Update(float deltaSeconds) {
	m_age += deltaSeconds;

	//Vector3 dir = Vector3(10.f * cos(m_age) + 5.f, 10.f * sin(m_age) + 5.f, -3.f);
	//m_lights[0].SetDirection(dir);
	//dir.Normalize();

	m_lights[1].SetConeWidth(-0.1f * cos(m_age) + 0.7f);

	g_theDebugRenderer->DrawDebugArrow(m_lights[0].GetPosition(), m_lights[0].GetPosition() + Vector3(0.f, 0.f, -1.f), RGBA::WHITE, DEBUG_DRAW_DEPTH_TEST_ON);

	//m_lights[0].SetRadius(10.f * cos(m_age) + 20.f);
	//m_lights[0].SetPosition(Vector3(8.f * cos(m_age) + 7.f, 8.f * sin(2 * m_age) / 2.f + 7.f, 3.f));
}
void LightSystem::Render() const {
	for (unsigned int i = 0; i < m_lights.size(); i++) {
		g_theDebugRenderer->DrawDebugSphere(m_lights[i].GetPosition(), 0.5f, m_lights[i].GetColor(), DEBUG_DRAW_DEPTH_TEST_ON);
	}
}

std::vector<Light3D> LightSystem::GetLights() const {
	return m_lights;
}