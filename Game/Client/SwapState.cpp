#include "pch.h"
#include "SwapState.h"
#include "Player.h"
#include "SkulSkill.h"
#include "RigidBody.h"
#include "Clock.h"
#include "AfterImage.h"
#include "Material.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Resources.h"
#include "AfterImageDrawScript.h"
#include "Scene.h"
#include "GlobalEffect.h"
#include "Transform.h"
#include "Scenes.h"
#include "EventManager.h"
#include "Transform.h"
#include "ObjectAddedToSceneEvent.h"
#include "Animator.h"
#include "Animation.h"

SwapState::SwapState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
{
}

void SwapState::Awake()
{
	CreateAndAddAfterImageToScene();
	CreateAndAddSwapEffectToScene();
}

void SwapState::Update()
{
	// Swap Skill
	weak_ptr<SkulSkill> pSwapSkill = m_pPlayer.lock()->GetActiveSkul()->GetSwapSkill();

	if (pSwapSkill.lock()->IsFinished())
	{
		AddChangeStateEvent(PLAYER_STATE::PATH);
	}
	else
	{
		pSwapSkill.lock()->Update();
	}

	if (CheckGrounded())
	{
		m_pPlayer.lock()->GetRigidBody()->RemoveGravity();
		m_pPlayer.lock()->GetRigidBody()->SetVelocity(AXIS::Y, 0.f);
	}
}

void SwapState::Enter()
{
	EnableAndInitAfterImage();
	EnableAndInitSwapEffect();

	m_pPlayer.lock()->SwapSkul();
	PlayAnimation();
	m_pPlayer.lock()->DisableSwapActiveFlag();

	weak_ptr<SkulSkill> pSwapSkill = m_pPlayer.lock()->GetActiveSkul()->GetSwapSkill();
	pSwapSkill.lock()->Enter();
	pSwapSkill.lock()->Activate();
}

void SwapState::Exit()
{
	weak_ptr<SkulSkill> pSwapSkill = m_pPlayer.lock()->GetActiveSkul()->GetSwapSkill();

	pSwapSkill.lock()->Exit();
	pSwapSkill.lock()->DeActivate();
}

void SwapState::PlayAnimation()
{
	weak_ptr<SkulSkill> pSwapSkill = m_pPlayer.lock()->GetActiveSkul()->GetSwapSkill();
	const wstring& szName = pSwapSkill.lock()->GetAnimationName();
	if (pSwapSkill.lock() && !szName.empty())
	{
		m_pPlayer.lock()->GetActiveSkul()->PlayAnimation(szName, true);
	}
}

void SwapState::CreateAndAddAfterImageToScene()
{
	shared_ptr<Scene> pActiveScene = GET_SINGLE(Scenes)->GetActiveScene();
	m_pAfterImage = make_shared<AfterImage>(AFTERIMAGE_TYPE::SWAP);
	shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"AfterImage")->Clone();
	shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();

	shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
	pMeshRenderer->SetMaterial(pMaterial);
	pMeshRenderer->SetMesh(pMesh);

	m_pAfterImage->AddComponent(pMeshRenderer);
	m_pAfterImage->AddComponent(make_shared<Transform>());

	m_pAfterImage->AddComponent(make_shared<AfterImageDrawScript>(m_pPlayer.lock()));

	m_pAfterImage->Disable();
	pActiveScene->AddGameObject(m_pAfterImage);
}

void SwapState::CreateAndAddSwapEffectToScene()
{
	m_pSwapEffect = make_shared<GlobalEffect>();
	m_pSwapEffect->AddComponent(make_shared<Transform>());
	m_pSwapEffect->AddComponent(make_shared<Animator>());

	shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();
	shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();

	shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
	pMeshRenderer->SetMaterial(pMaterial);
	pMeshRenderer->SetMesh(pMesh);

	const Vec3& vPlayerPos = m_pPlayer.lock()->GetTransform()->GetLocalPosition();

	m_pSwapEffect->GetTransform()->SetLocalPosition(vPlayerPos);
	m_pSwapEffect->AddComponent(pMeshRenderer);

	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();

	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->Load<Animation>(L"Swap_Particle", L"..\\Resources\\Animation\\SkulCommon\\swap_particle.anim");
	m_pSwapEffect->GetAnimator()->AddAnimation(L"Swap_Particle", pAnimation);

	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(m_pSwapEffect, eSceneType));
}

void SwapState::EnableAndInitAfterImage()
{
	m_pAfterImage->Enable();

	Vec3 vPlayerPos = Conv::PxVec3ToVec3(m_pPlayer.lock()->GetTransform()->GetPxTransform().p);
	const Vec3& vPlayerScale = m_pPlayer.lock()->GetActiveSkul()->GetTransform()->GetLocalScale();
	int32 iCurFrame = m_pPlayer.lock()->GetActiveSkul()->GetActiveAnimation().lock()->GetCurFrame();
	const FrameData& frameData = m_pPlayer.lock()->GetActiveSkul()->GetActiveAnimation().lock()->GetFrameDataList()[iCurFrame];
	const Vec2& vGlobalOffset = m_pPlayer.lock()->GetActiveSkul()->GetTransform()->GetGlobalOffset();

	m_pAfterImage->GetTransform()->SetGlobalOffset(vGlobalOffset);
	m_pAfterImage->GetTransform()->SetLocalPosition(vPlayerPos);
	m_pAfterImage->GetTransform()->SetLocalScale(vPlayerScale);
	m_pAfterImage->SetFrameData(frameData);
	m_pAfterImage->SetDirection(m_pPlayer.lock()->GetDirection());
}

void SwapState::EnableAndInitSwapEffect()
{
	float fDistance = 30.f;

	Vec3 vPlayerPos = Conv::PxVec3ToVec3(m_pPlayer.lock()->GetTransform()->GetPxTransform().p);
	const Vec3& vPlayerScale = m_pPlayer.lock()->GetActiveSkul()->GetTransform()->GetLocalScale();
	const Vec2& vGlobalOffset = m_pPlayer.lock()->GetActiveSkul()->GetTransform()->GetGlobalOffset();

	vPlayerPos.x -= fDistance;
	vPlayerPos.y += vPlayerScale.y / 3.f;

	m_pSwapEffect->Enable();
	m_pSwapEffect->GetTransform()->SetGlobalOffset(vGlobalOffset);
	m_pSwapEffect->GetTransform()->SetLocalPosition(vPlayerPos);
	m_pSwapEffect->GetAnimator()->Play(L"Swap_Particle", false);
}
