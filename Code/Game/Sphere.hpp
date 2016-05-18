/*
#pragma once

#define _USE_MATH_DEFINES

#include "Engine/Renderer/TheRenderer.hpp"
#include "Engine/Renderer/Mesh.hpp"
#include "Engine/Renderer/Shader.hpp"
#include "Engine/Renderer/ShaderProgram.hpp"
#include "Game/TheCamera.hpp"
#include "Game/GameCommon.hpp"

class Sphere {
public:
	//STRUCTORS
	Sphere();
	Sphere(float radius, const Vector3& position);

	//UPDATE RENDER
	void Update(float deltaSeconds);
	void Render() const;

	//GETTERS SETTERS
	void SetPosition(const Vector3& position);

private:
	void CreateMesh();

	Vector3 DebugExtendVector3(const Vector3& vec);

private:
	float m_radius;
	Vector3 m_position;

	Mesh m_mesh;
	Material m_material;

	Matrix4 m_model;

	float m_age;

	Vector3 m_lightPosition;
};*/