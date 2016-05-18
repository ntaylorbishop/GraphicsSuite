/*
#include "Game/Sphere.hpp"

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS
//---------------------------------------------------------------------------------------------------------------------------
Sphere::Sphere() 
	: m_radius(0.f)
	, m_position(Vector3(0.f, 0.f, 0.f))
	, m_age(0.f)
{ }
Sphere::Sphere(float radius, const Vector3& position) 
	: m_radius(radius)
	, m_position(position)
	, m_age(0.f)
{


	m_material = Material(RenderState(true, false, false, false), MATERIAL_METAL, "example");
	CreateMesh();

	m_model.ChangePosition(Vector3(0.f, 5.f, 0.f));
	m_mesh.UpdateModel(m_model);

	m_lightPosition = Vector3(0.f, -2.f, 0.f);
}

//---------------------------------------------------------------------------------------------------------------------------
//UPDATE RENDER
//---------------------------------------------------------------------------------------------------------------------------
void Sphere::Update(float deltaSeconds) {
	m_age += deltaSeconds * 2.f;

	m_lightPosition = Vector3(cos(m_age), 10.0f, sin(m_age));
}
void Sphere::Render() const {

	g_theRenderer->EnableBackfaceCulling();
	g_theDebugRenderer->DrawDebugSphere(m_lightPosition, 0.1f, RGBA::WHITE, DEBUG_DRAW_DEPTH_TEST_ON);
	m_mesh.DrawMeshWithMaterial(m_material, FOG_MIN_DISTANCE, FOG_MAX_DISTANCE, RGBA::GREEN);
}

//---------------------------------------------------------------------------------------------------------------------------
//GETTERS SETTERS
//---------------------------------------------------------------------------------------------------------------------------
void Sphere::SetPosition(const Vector3& position) {
	m_position = position;
	m_model.ChangePosition(m_position);
}

//---------------------------------------------------------------------------------------------------------------------------
//PRIVATE MEMBER FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------
void Sphere::CreateMesh() {
	std::vector<TexturedVertex_TBN> sphereVerts;
	std::vector<uint16_t> sphereIndices;
	float radius = 1.f;
	int rings = 100;
	int sectors = 100;
	int curRow = 0;
	int nextRow = 0;
	int nextS = 0;

	//r * R ==== UP
	//s * S ==== RIGHT

	float const R = 1.f / (float)(rings - 1);
	float const S = 1.f / (float)(sectors - 1);

	for (int r = 0; r < rings; ++r) {
		for (int s = 0; s < sectors; ++s) {
			float const x = (float)sin(2 * (float)M_PI * s * S) * (float)sin((float)M_PI * r * R);
			float const y = (float)cos(2 * (float)M_PI * s * S) * (float)sin((float)M_PI * r * R);
			float const z = (float)sin(-(float)M_PI_2 + (float)M_PI * r * R);

			Vector3 tangent = m_radius * Vector3((float)cos(2.f * M_PI * s * S) * (float)sin(M_PI * r * R), -(float)sin(2 * M_PI * s * S) * (float)sin(M_PI * r * R), (float)sin(-(float)M_PI_2 + (float)M_PI * r * R));
			Vector3 bitangent = m_radius * Vector3((float)sin(2 * (float)M_PI * s * S) * (float)cos((float)M_PI * r * R), (float)cos(2 * (float)M_PI * s * S) * (float)cos((float)M_PI * r * R), (float)cos((float)M_PI_2 + (float)M_PI * r * R));

			tangent.Normalize();
			bitangent.Normalize();

			sphereVerts.push_back(TexturedVertex_TBN(Vector3(x * radius, y * radius, -z * radius), RGBA::WHITE, Vector2(1 - s*S, r*R), tangent , bitangent));

			g_theDebugRenderer->DrawDebugLine(tangent, DebugExtendVector3(tangent), RGBA::MAGENTA, DEBUG_DRAW_DEPTH_TEST_DUAL);
			g_theDebugRenderer->DrawDebugLine(tangent, DebugExtendVector3(bitangent), RGBA::MAGENTA, DEBUG_DRAW_DEPTH_TEST_DUAL);

			curRow = r * sectors;
			nextRow = (r + 1) * sectors;
			nextS = (s + 1) % sectors;

			if (r < rings - 1) {
				sphereIndices.push_back((unsigned short)nextRow + (unsigned short)nextS);
				sphereIndices.push_back((unsigned short)nextRow + (unsigned short)s);
				sphereIndices.push_back((unsigned short)curRow + (unsigned short)s);

				sphereIndices.push_back((unsigned short)curRow + (unsigned short)nextS);
				sphereIndices.push_back((unsigned short)nextRow + (unsigned short)nextS);
				sphereIndices.push_back((unsigned short)curRow + (unsigned short)s);
			}
		}
	}

	m_mesh.UpdateMesh(sphereVerts, sphereIndices);
}

Vector3 Sphere::DebugExtendVector3(const Vector3& vec) {
	Vector3 dir = vec;
	dir.Normalize();
	dir = dir + vec;
	return dir;
}*/