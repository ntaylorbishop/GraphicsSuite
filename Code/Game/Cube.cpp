#include "Game/Cube.hpp"

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS
//---------------------------------------------------------------------------------------------------------------------------
Cube::Cube() { }
Cube::Cube(const Vector3& position)
{
	m_mesh = Mesh(VertexDefinition::TEXTUREDVERTEX_TBN);
	m_material = g_theMaterialManager->GetMaterial("Brick");
	CreateMesh();

	m_mesh.ChangePosition(position);
}

//---------------------------------------------------------------------------------------------------------------------------
//UPDATE RENDER
//---------------------------------------------------------------------------------------------------------------------------
void Cube::Update(float deltaSeconds) {
	UNREFERENCED_PARAMETER(deltaSeconds);
	//m_meshRenderer.Update(m_mesh);
}
void Cube::Render() const {
	m_meshRenderer.RenderMeshWithMaterial(m_mesh, m_material);
}

//---------------------------------------------------------------------------------------------------------------------------
//PRIVATE MEMBER FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------
void Cube::CreateMesh() {
	std::vector<TexturedVertex_TBN> cubeVerts;

	//FRONT FACE
	cubeVerts.push_back(TexturedVertex_TBN(Vector3(-1.5f, 1.5f,  1.5f),   RGBA::WHITE, Vector2(1.f, 0.f),  Vector3(-1.f, 0.f, 0.f), Vector3(0.f, 0.f, 1.f))); //tl
	cubeVerts.push_back(TexturedVertex_TBN(Vector3(-1.5f, 1.5f, -1.5f),   RGBA::WHITE, Vector2(1.f, 1.f),  Vector3(-1.f, 0.f, 0.f), Vector3(0.f, 0.f, 1.f))); //bl
	cubeVerts.push_back(TexturedVertex_TBN(Vector3( 1.5f, 1.5f, -1.5f),   RGBA::WHITE, Vector2(0.f, 1.f),  Vector3(-1.f, 0.f, 0.f), Vector3(0.f, 0.f, 1.f))); //br
	cubeVerts.push_back(TexturedVertex_TBN(Vector3( 1.5f, 1.5f,  1.5f),   RGBA::WHITE, Vector2(0.f, 0.f),  Vector3(-1.f, 0.f, 0.f), Vector3(0.f, 0.f, 1.f))); //tr
	//BACK FACE
	cubeVerts.push_back(TexturedVertex_TBN(Vector3(-1.5f, -1.5f, 1.5f),   RGBA::WHITE, Vector2(0.f, 0.f), Vector3(1.f, 0.f, 0.f), Vector3(0.f, 0.f, 1.f))); //tr
	cubeVerts.push_back(TexturedVertex_TBN(Vector3(-1.5f, -1.5f, -1.5f),  RGBA::WHITE, Vector2(0.f, 1.f), Vector3(1.f, 0.f, 0.f), Vector3(0.f, 0.f, 1.f))); //br
	cubeVerts.push_back(TexturedVertex_TBN(Vector3( 1.5f, -1.5f, -1.5f),  RGBA::WHITE, Vector2(1.f, 1.f), Vector3(1.f, 0.f, 0.f), Vector3(0.f, 0.f, 1.f))); //bl
	cubeVerts.push_back(TexturedVertex_TBN(Vector3( 1.5f, -1.5f, 1.5f),   RGBA::WHITE, Vector2(1.f, 0.f), Vector3(1.f, 0.f, 0.f), Vector3(0.f, 0.f, 1.f))); //tl
	//BOTTOM FACE																					
	cubeVerts.push_back(TexturedVertex_TBN(Vector3(-1.5f, 1.5f, -1.5f),  RGBA::WHITE, Vector2(0.f, 1.f), Vector3(1.f, 0.f, 0.f), Vector3(0.f, -1.f, 0.f))); //tl
	cubeVerts.push_back(TexturedVertex_TBN(Vector3(1.5f, 1.5f, -1.5f),   RGBA::WHITE, Vector2(1.f, 1.f), Vector3(1.f, 0.f, 0.f), Vector3(0.f, -1.f, 0.f))); //tr
	cubeVerts.push_back(TexturedVertex_TBN(Vector3(1.5f, -1.5f, -1.5f),  RGBA::WHITE, Vector2(1.f, 0.f), Vector3(1.f, 0.f, 0.f), Vector3(0.f, -1.f, 0.f))); //br
	cubeVerts.push_back(TexturedVertex_TBN(Vector3(-1.5f, -1.5f, -1.5f), RGBA::WHITE, Vector2(0.f, 0.f), Vector3(1.f, 0.f, 0.f), Vector3(0.f, -1.f, 0.f))); //bl
	//TOP FACE																						
	cubeVerts.push_back(TexturedVertex_TBN(Vector3(-1.5f, 1.5f, 1.5f),  RGBA::WHITE, Vector2(0.f, 0.f), Vector3(1.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f))); //tl
	cubeVerts.push_back(TexturedVertex_TBN(Vector3(-1.5f, -1.5f, 1.5f), RGBA::WHITE, Vector2(0.f, 1.f), Vector3(1.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f))); //bl
	cubeVerts.push_back(TexturedVertex_TBN(Vector3(1.5f, -1.5f, 1.5f),  RGBA::WHITE, Vector2(1.f, 1.f), Vector3(1.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f))); //br
	cubeVerts.push_back(TexturedVertex_TBN(Vector3(1.5f, 1.5f, 1.5f),   RGBA::WHITE, Vector2(1.f, 0.f), Vector3(1.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f))); //tr
	//RIGHT FACE																					
	cubeVerts.push_back(TexturedVertex_TBN(Vector3(1.5f, 1.5f, -1.5f),  RGBA::WHITE, Vector2(1.f, 1.f), Vector3(0.f, 1.f, 0.f), Vector3(0.f, 0.f, 1.f))); //tl
	cubeVerts.push_back(TexturedVertex_TBN(Vector3(1.5f, 1.5f, 1.5f),   RGBA::WHITE, Vector2(1.f, 0.f), Vector3(0.f, 1.f, 0.f), Vector3(0.f, 0.f, 1.f))); //tr
	cubeVerts.push_back(TexturedVertex_TBN(Vector3(1.5f, -1.5f, 1.5f),  RGBA::WHITE, Vector2(0.f, 0.f), Vector3(0.f, 1.f, 0.f), Vector3(0.f, 0.f, 1.f))); //br
	cubeVerts.push_back(TexturedVertex_TBN(Vector3(1.5f, -1.5f, -1.5f), RGBA::WHITE, Vector2(0.f, 1.f), Vector3(0.f, 1.f, 0.f), Vector3(0.f, 0.f, 1.f))); //bl
	//LEFT FACE																						
	cubeVerts.push_back(TexturedVertex_TBN(Vector3(-1.5f, 1.5f, -1.5f),  RGBA::WHITE, Vector2(0.f, 1.f), Vector3(0.f, -1.f, 0.f), Vector3(0.f, 0.f, 1.f))); //tl
	cubeVerts.push_back(TexturedVertex_TBN(Vector3(-1.5f, -1.5f, -1.5f), RGBA::WHITE, Vector2(1.f, 1.f), Vector3(0.f, -1.f, 0.f), Vector3(0.f, 0.f, 1.f))); //bl
	cubeVerts.push_back(TexturedVertex_TBN(Vector3(-1.5f, -1.5f, 1.5f),  RGBA::WHITE, Vector2(1.f, 0.f), Vector3(0.f, -1.f, 0.f), Vector3(0.f, 0.f, 1.f))); //br
	cubeVerts.push_back(TexturedVertex_TBN(Vector3(-1.5f, 1.5f, 1.5f),   RGBA::WHITE, Vector2(0.f, 0.f), Vector3(0.f, -1.f, 0.f), Vector3(0.f, 0.f, 1.f))); //tr

//IBO
	std::vector<uint16_t> cubeIndices = {
		0, 1, 2,
		0, 2, 3,

		4, 5, 6,
		4, 6, 7,

		8, 9, 10,
		8, 10, 11,

		12, 13, 14,
		12, 14, 15,

		16, 17, 18,
		16, 18, 19,

		20, 21, 22,
		20, 22, 23
	};

	m_mesh.UpdateMesh(cubeVerts, cubeIndices);
}