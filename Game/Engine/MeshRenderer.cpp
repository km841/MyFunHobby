#include "pch.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "Transform.h"
#include "Engine.h"

MeshRenderer::MeshRenderer()
	: Component(COMPONENT_TYPE::MESH_RENDERER)
{
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Render(shared_ptr<Camera> pCamera)
{
	GetTransform()->PushData(pCamera);
	m_pMaterial->PushGraphicData();

	CONST_BUFFER(CONSTANT_BUFFER_TYPE::TRANSFORM)->Mapping();
	CONST_BUFFER(CONSTANT_BUFFER_TYPE::MATERIAL)->Mapping();

	m_pMesh->Render();
}
