#include "pch.h"
#include "DebugRenderer.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "Transform.h"
#include "Engine.h"

DebugRenderer::DebugRenderer()
	: Component(COMPONENT_TYPE::DEBUG_RENDERER)
{

}

DebugRenderer::~DebugRenderer()
{
}

void DebugRenderer::Render(shared_ptr<Camera> pCamera)
{
	GetTransform()->PxPushData(pCamera);
	m_pMaterial->PushData();

	CONST_BUFFER(CONSTANT_BUFFER_TYPE::TRANSFORM)->Mapping();
	CONST_BUFFER(CONSTANT_BUFFER_TYPE::MATERIAL)->Mapping();

	m_pMesh->Render();
}
