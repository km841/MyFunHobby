#include "pch.h"
#include "Resources.h"
#include "Texture.h"
#include "Material.h"
#include "Shader.h"
#include "Engine.h"

void Resources::Init()
{
	CreateDefaultShader();
	CreateDefaultMaterial();
}

shared_ptr<Texture> Resources::CreateTexture(const wstring& szName, D3D11_BIND_FLAG eType, uint32 iWidth, uint32 iHeight)
{
	shared_ptr<Texture> pTexture = make_shared<Texture>();
	pTexture->Create(eType, iWidth, iHeight);
	Add(szName, pTexture);

	return pTexture;
}

shared_ptr<Texture> Resources::CreateTextureFromResource(const wstring& szName, D3D11_BIND_FLAG eType, ComPtr<ID3D11Texture2D> iTexture)
{
	shared_ptr<Texture> pTexture = make_shared<Texture>();
	pTexture->CreateFromTexture(eType, iTexture);
	Add(szName, pTexture);

	return pTexture;
}

shared_ptr<Mesh> Resources::LoadCubeMesh()
{
	shared_ptr<Mesh> pFindMesh = Get<Mesh>(L"Cube");
	if (pFindMesh)
		return pFindMesh;

	float w2 = 0.5f;
	float h2 = w2;
	float d2 = w2;

	std::vector<Vertex> vVertices(24);

	// front
	vVertices[0] = Vertex(Vec3(-w2, -h2, -d2), Vec2(0.f, 1.f));
	vVertices[1] = Vertex(Vec3(-w2, +h2, -d2), Vec2(0.f, 0.f));
	vVertices[2] = Vertex(Vec3(+w2, +h2, -d2), Vec2(1.f, 0.f));
	vVertices[3] = Vertex(Vec3(+w2, -h2, -d2), Vec2(1.f, 1.f));

	// back
	vVertices[4] = Vertex(Vec3(-w2, -h2, +d2), Vec2(0.f, 1.f));
	vVertices[5] = Vertex(Vec3(+w2, -h2, +d2), Vec2(1.f, 1.f));
	vVertices[6] = Vertex(Vec3(+w2, +h2, +d2), Vec2(1.f, 0.f));
	vVertices[7] = Vertex(Vec3(-w2, +h2, +d2), Vec2(0.f, 0.f));

	// top
	vVertices[8] = Vertex(Vec3(-w2, +h2, -d2), Vec2(0.f, 1.f));
	vVertices[9] = Vertex(Vec3(-w2, +h2, +d2), Vec2(0.f, 0.f));
	vVertices[10] = Vertex(Vec3(+w2, +h2, +d2), Vec2(1.f, 0.f));
	vVertices[11] = Vertex(Vec3(+w2, +h2, -d2), Vec2(1.f, 1.f));

	// bottom
	vVertices[12] = Vertex(Vec3(-w2, -h2, -d2), Vec2(1.f, 1.f));
	vVertices[13] = Vertex(Vec3(+w2, -h2, -d2), Vec2(1.f, 0.f));
	vVertices[14] = Vertex(Vec3(+w2, -h2, +d2), Vec2(0.f, 0.f));
	vVertices[15] = Vertex(Vec3(-w2, -h2, +d2), Vec2(0.f, 1.f));

	// left
	vVertices[16] = Vertex(Vec3(-w2, -h2, +d2), Vec2(0.f, 1.f));
	vVertices[17] = Vertex(Vec3(-w2, +h2, +d2), Vec2(0.f, 0.f));
	vVertices[18] = Vertex(Vec3(-w2, +h2, -d2), Vec2(1.f, 0.f));
	vVertices[19] = Vertex(Vec3(-w2, -h2, -d2), Vec2(1.f, 1.f));

	// right
	vVertices[20] = Vertex(Vec3(+w2, -h2, -d2), Vec2(0.f, 1.f));
	vVertices[21] = Vertex(Vec3(+w2, +h2, -d2), Vec2(0.f, 0.f));
	vVertices[22] = Vertex(Vec3(+w2, +h2, +d2), Vec2(1.f, 0.f));
	vVertices[23] = Vertex(Vec3(+w2, -h2, +d2), Vec2(1.f, 1.f));

	//-------

	std::vector<uint32> vIndices(36);

	// front
	vIndices[0] = 0; vIndices[1] = 1; vIndices[2] = 2;
	vIndices[3] = 0; vIndices[4] = 2; vIndices[5] = 3;

	// back
	vIndices[6] = 4; vIndices[7] = 5; vIndices[8] = 6;
	vIndices[9] = 4; vIndices[10] = 6; vIndices[11] = 7;

	// top
	vIndices[12] = 8; vIndices[13] = 9; vIndices[14] = 10;
	vIndices[15] = 8; vIndices[16] = 10; vIndices[17] = 11;

	// bottom
	vIndices[18] = 12; vIndices[19] = 13; vIndices[20] = 14;
	vIndices[21] = 12; vIndices[22] = 14; vIndices[23] = 15;

	// left
	vIndices[24] = 16; vIndices[25] = 17; vIndices[26] = 18;
	vIndices[27] = 16; vIndices[28] = 18; vIndices[29] = 19;

	// right
	vIndices[30] = 20; vIndices[31] = 21; vIndices[32] = 22;
	vIndices[33] = 20; vIndices[34] = 22; vIndices[35] = 23;

	shared_ptr<Mesh> pMesh = make_shared<Mesh>();
	pMesh->Init(vVertices, vIndices);

	Add(L"Cube", pMesh);

	return pMesh;
}

shared_ptr<Mesh> Resources::LoadRectMesh()
{
	shared_ptr<Mesh> pFindMesh = Get<Mesh>(L"Rect");
	if (pFindMesh)
		return pFindMesh;

	std::vector<Vertex> vVertices;

	vVertices.push_back(Vertex(Vec3(-1.f, 1.f, 0.f), Vec2(0.f, 0.f)));
	vVertices.push_back(Vertex(Vec3(1.f, 1.f, 0.f), Vec2(1.f, 0.f)));
	vVertices.push_back(Vertex(Vec3(1.f, -1.f, 0.f), Vec2(1.f, 1.f)));
	vVertices.push_back(Vertex(Vec3(-1.f, -1.f, 0.f), Vec2(0.f, 1.f)));

	std::vector<uint32> vIndices(6);

	vIndices[0] = 0;
	vIndices[1] = 1;
	vIndices[2] = 2;

	vIndices[3] = 0;
	vIndices[4] = 2;
	vIndices[5] = 3;

	shared_ptr<Mesh> pMesh = make_shared<Mesh>();
	pMesh->Init(vVertices, vIndices);

	Add<Mesh>(L"Rect", pMesh);

	return pMesh;
}

void Resources::CreateDefaultShader()
{
	// Alpha
	{
		ShaderInfo shaderInfo =
		{
			SHADER_TYPE::FORWARD,
			DEPTH_STENCIL_TYPE::LESS,
			RASTERIZER_TYPE::CULL_BACK,
			BLEND_TYPE::ALPHA_BLEND
		};

		shared_ptr<Shader> pShader = make_shared<Shader>();
		pShader->CreateGraphicsShader(L"..\\Resources\\Shader\\alpha.fx", shaderInfo);

		Add<Shader>(L"Alpha", pShader);
	}

	// Preview
	{
		ShaderInfo shaderInfo =
		{
			SHADER_TYPE::FORWARD,
			DEPTH_STENCIL_TYPE::LESS,
			RASTERIZER_TYPE::CULL_BACK,
			BLEND_TYPE::ALPHA_BLEND
		};

		shared_ptr<Shader> pShader = make_shared<Shader>();
		pShader->CreateGraphicsShader(L"..\\Resources\\Shader\\preview.fx", shaderInfo);

		Add<Shader>(L"Preview", pShader);
	}

	// Debug Geometry
	{
		ShaderInfo shaderInfo =
		{
			SHADER_TYPE::FORWARD,
			DEPTH_STENCIL_TYPE::LESS,
			RASTERIZER_TYPE::CULL_BACK,
			BLEND_TYPE::DEFAULT,
			D3D_PRIMITIVE_TOPOLOGY_LINESTRIP
		};

		shared_ptr<Shader> pShader = make_shared<Shader>();
		pShader->CreateGraphicsShader(L"..\\Resources\\Shader\\debug_geometry.fx", shaderInfo);

		Add<Shader>(L"DebugGeometry", pShader);
	}

	// Frame Divider
	{
		ShaderInfo shaderInfo =
		{
			SHADER_TYPE::FORWARD,
			DEPTH_STENCIL_TYPE::LESS,
			RASTERIZER_TYPE::CULL_BACK,
			BLEND_TYPE::DEFAULT,
			D3D_PRIMITIVE_TOPOLOGY_LINESTRIP
		};

		shared_ptr<Shader> pShader = make_shared<Shader>();
		pShader->CreateGraphicsShader(L"..\\Resources\\Shader\\frame_divider.fx", shaderInfo);

		Add<Shader>(L"FrameDivider", pShader);
	}

	// Forward
	{
		ShaderInfo shaderInfo =
		{
			SHADER_TYPE::FORWARD,
			DEPTH_STENCIL_TYPE::LESS,
			RASTERIZER_TYPE::CULL_BACK,
			BLEND_TYPE::ALPHA_BLEND
		};

		shared_ptr<Shader> pShader = make_shared<Shader>();
		pShader->CreateGraphicsShader(L"..\\Resources\\Shader\\forward.fx", shaderInfo);

		Add<Shader>(L"Forward", pShader);
	}

	// Grid
	{
		shared_ptr<Shader> pShader = make_shared<Shader>();
		pShader->CreateGraphicsShader(L"..\\Resources\\Shader\\grid.fx");

		Add<Shader>(L"Grid", pShader);
	}

	// Compute
	{
		shared_ptr<Shader> pShader = make_shared<Shader>();
		pShader->CreateComputeShader(L"..\\Resources\\Shader\\compute.fx", "CS_Main", "cs_5_0");
		Add<Shader>(L"Compute", pShader);
	}
}

void Resources::CreateDefaultMaterial()
{
	// Alpha
	{
		shared_ptr<Material> pMaterial = make_shared<Material>();
		shared_ptr<Shader> pShader = Get<Shader>(L"Alpha");
		pMaterial->SetShader(pShader);

		Add<Material>(L"Alpha", pMaterial);
	}

	// Preview
	{
		shared_ptr<Material> pMaterial = make_shared<Material>();
		shared_ptr<Shader> pShader = Get<Shader>(L"Preview");
		pMaterial->SetShader(pShader);

		Add<Material>(L"Preview", pMaterial);
	}

	// Forward
	{
		shared_ptr<Material> pMaterial = make_shared<Material>();
		shared_ptr<Shader> pShader = Get<Shader>(L"Forward");

		pMaterial->SetShader(pShader);
		Add<Material>(L"Forward", pMaterial);
	}
	
	// Debug Geometry
	{
		shared_ptr<Material> pMaterial = make_shared<Material>();
		shared_ptr<Shader> pShader = Get<Shader>(L"DebugGeometry");

		pMaterial->SetShader(pShader);
		Add<Material>(L"DebugGeometry", pMaterial);
	}

	// Frame Divider
	{
		shared_ptr<Material> pMaterial = make_shared<Material>();
		shared_ptr<Shader> pShader = Get<Shader>(L"FrameDivider");

		pMaterial->SetShader(pShader);
		Add<Material>(L"FrameDivider", pMaterial);
	}

	// Grid
	{
		shared_ptr<Material> pMaterial = make_shared<Material>();
		shared_ptr<Shader> pShader = Get<Shader>(L"Grid");

		pMaterial->SetShader(pShader);
		Add<Material>(L"Grid", pMaterial);
	}

	// Atlas
	{
		shared_ptr<Material> pMaterial = make_shared<Material>();
		shared_ptr<Shader> pShader = Get<Shader>(L"Forward");

		pMaterial->SetShader(pShader);
		Add<Material>(L"Atlas", pMaterial);
	}

	// Compute
	{
		shared_ptr<Material> pMaterial = make_shared<Material>();
		shared_ptr<Shader> pShader = Get<Shader>(L"Compute");

		pMaterial->SetShader(pShader);
		Add<Material>(L"Compute", pMaterial);
	}

}
