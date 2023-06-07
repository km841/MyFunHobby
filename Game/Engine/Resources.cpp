#include "pch.h"
#include "Resources.h"
#include "Texture.h"
#include "Material.h"
#include "Shader.h"
#include "Engine.h"
#include "SpineTextureLoader.h"
#include "SpineResource.h"

void Resources::Init()
{

	CreateDefaultShader();
	CreateDefaultMaterial();
}

void Resources::Destroy()
{
	for (auto& pResource : m_arrResources[static_cast<uint8>(OBJECT_TYPE::SPINE)])
	{
		pResource.second->Destroy();
		pResource.second.reset();
		pResource.second = nullptr;
	}

	//static_cast<spine::DefaultSpineExtension*>(spine::getDefaultExtension())->Destroy();
}

shared_ptr<Texture> Resources::CreateTexture(const wstring& szName, DXGI_FORMAT eFormat, uint32 eType, uint32 iWidth, uint32 iHeight)
{
	shared_ptr<Texture> pTexture = make_shared<Texture>();
	pTexture->Create(eType, eFormat, iWidth, iHeight);
	Add(szName, pTexture);

	return pTexture;
}

shared_ptr<Texture> Resources::CreateTextureFromResource(const wstring& szName, DXGI_FORMAT eFormat, uint32 eType, ComPtr<ID3D11Texture2D> iTexture)
{
	shared_ptr<Texture> pTexture = make_shared<Texture>();
	pTexture->CreateFromTexture(eType, eFormat, iTexture);
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

shared_ptr<Mesh> Resources::LoadCircleMesh()
{
	shared_ptr<Mesh> findMesh = Get<Mesh>(L"Circle");
	if (findMesh)
		return findMesh;

	float fRadius = 0.5f; // ±¸ÀÇ ¹ÝÁö¸§
	uint32 iStackCount = 20; // °¡·Î ºÐÇÒ
	uint32 iSliceCount = 20; // ¼¼·Î ºÐÇÒ

	std::vector<Vertex> vVertices;

	Vertex vertex;

	// ºÏ±Ø
	vertex.vPos = Vec3(0.0f, fRadius, 0.0f);
	vertex.vUV = Vec2(0.5f, 0.0f);
	vertex.vNormal = vertex.vPos;
	vertex.vNormal.Normalize();
	vVertices.push_back(vertex);

	float fStackAngle = XM_PI / iStackCount;
	float fSliceAngle = XM_2PI / iSliceCount;

	float fDeltaU = 1.f / static_cast<float>(iSliceCount);
	float fDeltaV = 1.f / static_cast<float>(iStackCount);

	for (uint32 y = 1; y <= iStackCount - 1; ++y)
	{
		float fPhi = y * fStackAngle;

		// °í¸®¿¡ À§Ä¡ÇÑ Á¤Á¡
		for (uint32 x = 0; x <= iSliceCount; ++x)
		{
			float fTheta = x * fSliceAngle;

			vertex.vPos.x = fRadius * sinf(fPhi) * cosf(fTheta);
			vertex.vPos.y = fRadius * cosf(fPhi);

			vertex.vUV = Vec2(fDeltaU * x, fDeltaV * y);

			vertex.vNormal = vertex.vPos;
			vertex.vNormal.Normalize();

			vVertices.push_back(vertex);
		}
	}

	// ³²±Ø
	vertex.vPos = Vec3(0.0f, -fRadius, 0.0f);
	vertex.vUV = Vec2(0.5f, 1.0f);
	vertex.vNormal = vertex.vPos;
	vertex.vNormal.Normalize();
	vVertices.push_back(vertex);

	std::vector<uint32> vIndices(36);

	// ºÏ±Ø ÀÎµ¦½º
	for (uint32 i = 0; i <= iSliceCount; ++i)
	{
		//  [0]
		//   |  \
		//  [i+1]-[i+2]
		vIndices.push_back(0);
		vIndices.push_back(i + 2);
		vIndices.push_back(i + 1);
	}

	// ¸öÅë ÀÎµ¦½º
	uint32 iRingVertexCount = iSliceCount + 1;
	for (uint32 y = 0; y < iStackCount - 2; ++y)
	{
		for (uint32 x = 0; x < iSliceCount; ++x)
		{
			//  [y, x]-[y, x+1]
			//  |		/
			//  [y+1, x]
			vIndices.push_back(1 + (y)*iRingVertexCount + (x));
			vIndices.push_back(1 + (y)*iRingVertexCount + (x + 1));
			vIndices.push_back(1 + (y + 1) * iRingVertexCount + (x));
			//		 [y, x+1]
			//		 /	  |
			//  [y+1, x]-[y+1, x+1]
			vIndices.push_back(1 + (y + 1) * iRingVertexCount + (x));
			vIndices.push_back(1 + (y)*iRingVertexCount + (x + 1));
			vIndices.push_back(1 + (y + 1) * iRingVertexCount + (x + 1));
		}
	}

	// ³²±Ø ÀÎµ¦½º
	uint32 iBottomIndex = static_cast<uint32>(vVertices.size()) - 1;
	uint32 iLastRingStartIndex = iBottomIndex - iRingVertexCount;
	for (uint32 i = 0; i < iSliceCount; ++i)
	{
		//  [last+i]-[last+i+1]
		//  |      /
		//  [bottom]
		vIndices.push_back(iBottomIndex);
		vIndices.push_back(iLastRingStartIndex + i);
		vIndices.push_back(iLastRingStartIndex + i + 1);
	}

	shared_ptr<Mesh> pMesh = make_shared<Mesh>();
	pMesh->Init(vVertices, vIndices);
	Add(L"Circle", pMesh);

	return pMesh;
}

shared_ptr<Mesh> Resources::LoadPointMesh()
{
	shared_ptr<Mesh> pFindMesh = Get<Mesh>(L"Point");
	if (pFindMesh)
		return pFindMesh;

	std::vector<Vertex> vVertices(1);
	vVertices[0] = Vertex(Vec3(0.f, 0.f, 0.f), Vec2(0.5f, 0.5f), Vec3(0.f, 0.f, -1.f));


	std::vector<uint32> vIndices(1);
	vIndices[0] = 0;

	shared_ptr<Mesh> pMesh = make_shared<Mesh>();
	pMesh->Init(vVertices, vIndices);

	Add<Mesh>(L"Point", pMesh);
	return pMesh;
}


shared_ptr<Animation> Resources::LoadAnimation(const wstring& szKey, const wstring& szPath)
{
	shared_ptr<Animation> pAnimation = make_shared<Animation>();
	pAnimation->Load(szPath);
	pAnimation->SetName(szKey);
	return pAnimation;
}

shared_ptr<SpineResource> Resources::LoadSkeletonData(const string& szKey, const string& szAtlasPath, const string& szBinaryPath)
{
	shared_ptr<SpineResource> pSpineResource = make_shared<SpineResource>(szAtlasPath, szBinaryPath);
	pSpineResource->Init();

	Add<SpineResource>(s2ws(szKey), pSpineResource);
	return pSpineResource;
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

	// Mirror
	{
		ShaderInfo shaderInfo =
		{
			SHADER_TYPE::FORWARD,
			DEPTH_STENCIL_TYPE::LESS,
			RASTERIZER_TYPE::CULL_BACK,
			BLEND_TYPE::ALPHA_BLEND
		};

		shared_ptr<Shader> pShader = make_shared<Shader>();
		pShader->CreateGraphicsShader(L"..\\Resources\\Shader\\mirror.fx", shaderInfo);

		Add<Shader>(L"Mirror", pShader);
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

		ShaderArg shaderArg =
		{
			"VS_DirLight",
			"",
			"PS_DirLight"
		};

		shared_ptr<Shader> pShader = make_shared<Shader>();
		pShader->CreateGraphicsShader(L"..\\Resources\\Shader\\lighting.fx",shaderInfo, shaderArg);

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

		ShaderArg shaderArg =
		{
			"VS_PointLight",
			"",
			"PS_PointLight"
		};

		shared_ptr<Shader> pShader = make_shared<Shader>();
		pShader->CreateGraphicsShader(L"..\\Resources\\Shader\\lighting.fx", shaderInfo, shaderArg);

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

	// Deferred
	{
		ShaderInfo shaderInfo =
		{
			SHADER_TYPE::DEFERRED,
		};

		shared_ptr<Shader> pShader = make_shared<Shader>();
		pShader->CreateGraphicsShader(L"..\\Resources\\Shader\\monster_deferred.fx", shaderInfo);
		Add<Shader>(L"Monster_Deferred", pShader);
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

	// Monster Health Bar
	{
		ShaderInfo shaderInfo =
		{
			SHADER_TYPE::FORWARD,
			DEPTH_STENCIL_TYPE::LESS,
			RASTERIZER_TYPE::CULL_BACK,
			BLEND_TYPE::ALPHA_BLEND
		};

		shared_ptr<Shader> pShader = make_shared<Shader>();
		pShader->CreateGraphicsShader(L"..\\Resources\\Shader\\monster_hp.fx", shaderInfo);

		Add<Shader>(L"MonsterHP", pShader);
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


	// Particle
	{
		ShaderInfo shaderInfo =
		{
			SHADER_TYPE::FORWARD,
			DEPTH_STENCIL_TYPE::LESS_NO_WRITE,
			RASTERIZER_TYPE::CULL_NONE,
			BLEND_TYPE::ALPHA_BLEND,
			D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST
		};

		ShaderArg shaderArg =
		{
			"VS_Main",
			"GS_Main",
			"PS_Main"
		};

		shared_ptr<Shader> pShader = make_shared<Shader>();
		pShader->CreateGraphicsShader(L"..\\Resources\\Shader\\particle.fx", shaderInfo, shaderArg);
		Add<Shader>(L"Particle", pShader);
	}

	// Compute Particle
	{
		shared_ptr<Shader> pShader = make_shared<Shader>();
		pShader->CreateComputeShader(L"..\\Resources\\Shader\\particle.fx", "CS_Main", "cs_5_0");
		Add<Shader>(L"ComputeParticle", pShader);
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
		pShader->CreateGraphicsShader(L"..\\Resources\\Shader\\inventory_info.fx", shaderInfo);

		Add<Shader>(L"InventoryInfo", pShader);
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

	// Mirror
	{
		shared_ptr<Material> pMaterial = make_shared<Material>();
		shared_ptr<Shader> pShader = Get<Shader>(L"Mirror");

		pMaterial->SetTexture(2, Get<Texture>(L"VelocityTarget"));

		pMaterial->SetShader(pShader);
		Add<Material>(L"Mirror", pMaterial);
	}

	// Deferred
	{
		shared_ptr<Material> pMaterial = make_shared<Material>();
		shared_ptr<Shader> pShader = Get<Shader>(L"Deferred");

		pMaterial->SetShader(pShader);
		Add<Material>(L"Deferred", pMaterial);
	}

	// Monster Deferred
	{
		shared_ptr<Material> pMaterial = make_shared<Material>();
		shared_ptr<Shader> pShader = Get<Shader>(L"Monster_Deferred");

		pMaterial->SetShader(pShader);
		Add<Material>(L"Monster_Deferred", pMaterial);
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

	// Monster HP
	{
		shared_ptr<Material> pMaterial = make_shared<Material>();
		shared_ptr<Shader> pShader = Get<Shader>(L"MonsterHP");

		pMaterial->SetShader(pShader);
		Add<Material>(L"MonsterHP", pMaterial);
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
		pMaterial->SetTexture(1, GET_SINGLE(Resources)->Get<Texture>(L"VelocityTarget"));
		pMaterial->SetTexture(2, GET_SINGLE(Resources)->Get<Texture>(L"DiffuseLightTarget"));

		Add<Material>(L"Final", pMaterial);
	}

	// Particle
	{
		shared_ptr<Material> pMaterial = make_shared<Material>();
		shared_ptr<Shader> pShader = Get<Shader>(L"Particle");
		pMaterial->SetShader(pShader);
		Add<Material>(L"Particle", pMaterial);
	}

	// Compute Particle
	{
		shared_ptr<Material> pMaterial = make_shared<Material>();
		shared_ptr<Shader> pShader = Get<Shader>(L"ComputeParticle");
		pMaterial->SetShader(pShader);
		Add<Material>(L"ComputeParticle", pMaterial);
	}

	// Particle
	{
		shared_ptr<Material> pMaterial = make_shared<Material>();
		shared_ptr<Shader> pShader = Get<Shader>(L"InventoryInfo");
		pMaterial->SetShader(pShader);
		Add<Material>(L"InventoryInfo", pMaterial);
	}
}
