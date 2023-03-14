#include "pch.h"
#include "Mesh.h"
#include "Engine.h"

Mesh::Mesh()
	: Object(OBJECT_TYPE::MESH)
	, m_iIndexCount(0)
{
}

Mesh::~Mesh()
{
}

void Mesh::Init(const std::vector<Vertex>& vVertices, const std::vector<uint32>& vIndices)
{
	CreateVertexBuffer(vVertices);
	CreateIndexBuffer(vIndices);
}

void Mesh::Render()
{
	uint32 iStride = sizeof(Vertex);
	uint32 iOffset = 0;

	CONTEXT->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &iStride, &iOffset);
	CONTEXT->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	CONTEXT->DrawIndexed(m_iIndexCount, 0, 0);
}

void Mesh::CreateVertexBuffer(const std::vector<Vertex>& vVertices)
{
	uint32 iCount = static_cast<uint32>(vVertices.size());
	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = sizeof(Vertex) * iCount;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA subData = {};
	subData.pSysMem = vVertices.data();

	HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &m_pVertexBuffer);
	assert(SUCCEEDED(hr));
}

void Mesh::CreateIndexBuffer(const std::vector<uint32>& vIndices)
{
	m_iIndexCount = static_cast<uint32>(vIndices.size());
	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = sizeof(uint32) * m_iIndexCount;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
	desc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA subData = {};
	subData.pSysMem = vIndices.data();

	HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &m_pIndexBuffer);
	assert(SUCCEEDED(hr));
}


