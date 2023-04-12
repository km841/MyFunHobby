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

shared_ptr<Texture> Resources::CreateTexture(const wstring& szName, uint32 eType, uint32 iWidth, uint32 iHeight)
{
	shared_ptr<Texture> pTexture = make_shared<Texture>();
	pTexture->Create(eType, iWidth, iHeight);
	Add(szName, pTexture);

	return pTexture;
}

shared_ptr<Texture> Resources::CreateTextureFromResource(const wstring& szName, uint32 eType, ComPtr<ID3D11Texture2D> iTexture)
{
	shared_ptr<Texture> pTexture = make_shared<Texture>();
	pTexture->CreateFromTexture(eType, iTexture);
	Add(szName, pTexture);

	return pTexture;
}


shared_ptr<Mesh> Resources::LoadRectMesh()
{
	shared_ptr<Mesh> pFindMesh = Get<Mesh>(L"Rect");
	if (pFindMesh)
		return pFindMesh;

	std::vector<Vertex> vVertices;

	vVertices.push_back(Vertex(Vec3(-1.f, 1.f, 0.f), Vec2(0.f, 0.f), Vec3(0.f, 0.f, -1.f)));
	vVertices.push_back(Vertex(Vec3(1.f, 1.f, 0.f), Vec2(1.f, 0.f), Vec3(0.f, 0.f, -1.f)));
	vVertices.push_back(Vertex(Vec3(1.f, -1.f, 0.f), Vec2(1.f, 1.f), Vec3(0.f, 0.f, -1.f)));
	vVertices.push_back(Vertex(Vec3(-1.f, -1.f, 0.f), Vec2(0.f, 1.f), Vec3(0.f, 0.f, -1.f)));

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

	// DirLight
	{
		ShaderInfo shaderInfo =
		{
			SHADER_TYPE::LIGHTING,
			DEPTH_STENCIL_TYPE::NO_DEPTH_TEST_NO_WRITE,
			RASTERIZER_TYPE::CULL_NONE,
			BLEND_TYPE::ONE_TO_ONE_BLEND
		};

		shared_ptr<Shader> pShader = make_shared<Shader>();
		pShader->CreateGraphicsShader(L"..\\Resources\\Shader\\lighting.fx",shaderInfo, "VS_DirLight", "PS_DirLight");

		Add<Shader>(L"DirLight", pShader);
	}

	// PointLight
	{
		ShaderInfo shaderInfo =
		{
			SHADER_TYPE::LIGHTING,
			DEPTH_STENCIL_TYPE::NO_DEPTH_TEST_NO_WRITE,
			RASTERIZER_TYPE::CULL_NONE,
			BLEND_TYPE::ONE_TO_ONE_BLEND
		};

		shared_ptr<Shader> pShader = make_shared<Shader>();
		pShader->CreateGraphicsShader(L"..\\Resources\\Shader\\lighting.fx", shaderInfo, "VS_PointLight", "PS_PointLight");

		Add<Shader>(L"PointLight", pShader);
	}


	// Deferred
	{
		ShaderInfo shaderInfo =
		{
			SHADER_TYPE::DEFERRED,
		};

		shared_ptr<Shader> pShader = make_shared<Shader>();
		pShader->CreateGraphicsShader(L"..\\Resources\\Shader\\deferred.fx", shaderInfo);
		Add<Shader>(L"Deferred", pShader);
	}

	// Fade In / Out
	{
		ShaderInfo shaderInfo =
		{
			SHADER_TYPE::FORWARD,
			DEPTH_STENCIL_TYPE::LESS,
			RASTERIZER_TYPE::CULL_BACK,
			BLEND_TYPE::ALPHA_BLEND
		};

		shared_ptr<Shader> pShader = make_shared<Shader>();
		pShader->CreateGraphicsShader(L"..\\Resources\\Shader\\fade_in_out.fx", shaderInfo);

		Add<Shader>(L"FadeInOut", pShader);
	}

	// Health Bar
	{
		ShaderInfo shaderInfo =
		{
			SHADER_TYPE::FORWARD,
			DEPTH_STENCIL_TYPE::LESS,
			RASTERIZER_TYPE::CULL_BACK,
			BLEND_TYPE::ALPHA_BLEND
		};

		shared_ptr<Shader> pShader = make_shared<Shader>();
		pShader->CreateGraphicsShader(L"..\\Resources\\Shader\\hp.fx", shaderInfo);

		Add<Shader>(L"HP", pShader);
	}

	// Compute
	{
		shared_ptr<Shader> pShader = make_shared<Shader>();
		pShader->CreateComputeShader(L"..\\Resources\\Shader\\compute.fx", "CS_Main", "cs_5_0");
		Add<Shader>(L"Compute", pShader);
	}

	// AfterImage
	{
		ShaderInfo shaderInfo =
		{
			SHADER_TYPE::FORWARD,
			DEPTH_STENCIL_TYPE::LESS,
			RASTERIZER_TYPE::CULL_BACK,
			BLEND_TYPE::ALPHA_BLEND
		};

		shared_ptr<Shader> pShader = make_shared<Shader>();
		pShader->CreateGraphicsShader(L"..\\Resources\\Shader\\afterimage.fx", shaderInfo);

		Add<Shader>(L"AfterImage", pShader);
	}

	// Cooldown
	{
		ShaderInfo shaderInfo =
		{
			SHADER_TYPE::FORWARD,
			DEPTH_STENCIL_TYPE::LESS,
			RASTERIZER_TYPE::CULL_BACK,
			BLEND_TYPE::ALPHA_BLEND
		};

		shared_ptr<Shader> pShader = make_shared<Shader>();
		pShader->CreateGraphicsShader(L"..\\Resources\\Shader\\cooldown.fx", shaderInfo);

		Add<Shader>(L"Cooldown", pShader);
	}

	// Effect
	{
		ShaderInfo shaderInfo =
		{
			SHADER_TYPE::LIGHTING,
			DEPTH_STENCIL_TYPE::LESS,
			RASTERIZER_TYPE::CULL_BACK,
			BLEND_TYPE::DEFAULT
		};

		shared_ptr<Shader> pShader = make_shared<Shader>();
		pShader->CreateGraphicsShader(L"..\\Resources\\Shader\\effect.fx", shaderInfo);

		Add<Shader>(L"Effect", pShader);
	}

	// Final
	{
		ShaderInfo shaderInfo =
		{
			SHADER_TYPE::LIGHTING,
			DEPTH_STENCIL_TYPE::NO_DEPTH_TEST_NO_WRITE,
			RASTERIZER_TYPE::CULL_BACK,
			BLEND_TYPE::DEFAULT
		};

		shared_ptr<Shader> pShader = make_shared<Shader>();
		pShader->CreateGraphicsShader(L"..\\Resources\\Shader\\final.fx", shaderInfo);

		Add<Shader>(L"Final", pShader);
	}
}

void Resources::CreateDefaultMaterial()
{
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

	// Deferred
	{
		shared_ptr<Material> pMaterial = make_shared<Material>();
		shared_ptr<Shader> pShader = Get<Shader>(L"Deferred");

		pMaterial->SetShader(pShader);
		Add<Material>(L"Deferred", pMaterial);
	}

	// Dir Light
	{
		shared_ptr<Material> pMaterial = make_shared<Material>();
		shared_ptr<Shader> pShader = Get<Shader>(L"DirLight");

		pMaterial->SetTexture(0, Get<Texture>(L"PositionTarget"));

		pMaterial->SetShader(pShader);
		Add<Material>(L"DirLight", pMaterial);
	}

	// Point Light
	{
		Vec2 vResolution = Vec2(static_cast<float>(g_pEngine->GetWidth()), static_cast<float>(g_pEngine->GetHeight()));

		shared_ptr<Material> pMaterial = make_shared<Material>();
		shared_ptr<Shader> pShader = Get<Shader>(L"PointLight");

		pMaterial->SetTexture(0, Get<Texture>(L"PositionTarget"));
		pMaterial->SetVec2(0, vResolution);

		pMaterial->SetShader(pShader);
		Add<Material>(L"PointLight", pMaterial);
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

	// Fade In / Out
	{
		shared_ptr<Material> pMaterial = make_shared<Material>();
		shared_ptr<Shader> pShader = Get<Shader>(L"FadeInOut");

		pMaterial->SetShader(pShader);
		Add<Material>(L"FadeInOut", pMaterial);
	}

	// HP
	{
		shared_ptr<Material> pMaterial = make_shared<Material>();
		shared_ptr<Shader> pShader = Get<Shader>(L"HP");

		pMaterial->SetShader(pShader);
		Add<Material>(L"HP", pMaterial);
	}

	// AfterImage
	{
		shared_ptr<Material> pMaterial = make_shared<Material>();
		shared_ptr<Shader> pShader = Get<Shader>(L"AfterImage");

		pMaterial->SetShader(pShader);
		Add<Material>(L"AfterImage", pMaterial);
	}

	// Cooldown
	{
		shared_ptr<Material> pMaterial = make_shared<Material>();
		shared_ptr<Shader> pShader = Get<Shader>(L"Cooldown");

		pMaterial->SetShader(pShader);
		Add<Material>(L"Cooldown", pMaterial);
	}

	// Effect
	{
		shared_ptr<Material> pMaterial = make_shared<Material>();
		shared_ptr<Shader> pShader = Get<Shader>(L"Effect");
		pMaterial->SetShader(pShader);

		
		Add<Material>(L"Effect", pMaterial);
	}

	// Final
	{
		shared_ptr<Material> pMaterial = make_shared<Material>();
		shared_ptr<Shader> pShader = Get<Shader>(L"Final");
		pMaterial->SetShader(pShader);

		pMaterial->SetTexture(0, GET_SINGLE(Resources)->Get<Texture>(L"DiffuseTarget"));
		pMaterial->SetTexture(1, GET_SINGLE(Resources)->Get<Texture>(L"DiffuseLightTarget"));

		Add<Material>(L"Final", pMaterial);
	}

}
