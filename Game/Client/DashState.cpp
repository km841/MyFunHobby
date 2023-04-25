#include "pch.h"
#include "DashState.h"
#include "Animator.h"
#include "Input.h"
#include "EventManager.h"
#include "PlayerChangeStateEvent.h"
#include "RigidBody.h"
#include "Transform.h"
#include "Physical.h"
#include "Collider.h"
#include "Scenes.h"
#include "Engine.h"
#include "Clock.h"
#include "AfterImage.h"
#include "Material.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Resources.h"
#include "AfterImageDrawScript.h"
#include "Scene.h"
#include "GlobalEffect.h"

DashState::DashState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
	, m_tDuration(0.2f)
	, m_fDashSpeed(1000.f)
	, m_iAfterImageMaxCount(4)
	, m_fAfterImageTimeOffset(0.25f)
{
	m_ePlayerState = PLAYER_STATE::DASH;
}

void DashState::Awake()
{
	CreateAndAddAfterImagesToScene();
}

void DashState::Update()
{
	m_tDuration.Update(DELTA_TIME);

	uint8 iDirection = static_cast<uint8>(m_pPlayer.lock()->GetDirection());
	m_pPlayer.lock()->GetRigidBody()->SetVelocity(AXIS::X, iDirection ? -m_fDashSpeed : m_fDashSpeed);

	// Path State ÀüÀÌ
	if (m_tDuration.IsFinished())
	{
		AddChangeStateEvent(PLAYER_STATE::PATH);
		return;
	}

	float fProgress = m_tDuration.GetProgress();
	for (int32 i = 0; i < m_iAfterImageMaxCount; ++i)
	{
		if ((fProgress >= m_fAfterImageTimeOffset + (i * m_fAfterImageTimeOffset)) && m_vAfterImages[i]->IsDisable())
		{
			EnableAndInitAfterImage(m_vAfterImages[i]);
		}
	}
}

void DashState::Enter()
{
	m_tDuration.Start();

	PlayAnimation();
	m_pPlayer.lock()->GetRigidBody()->RemoveGravity();
	m_pPlayer.lock()->GetRigidBody()->SetVelocity(AXIS::Y, 0.f);
	m_pPlayer.lock()->GetActiveSkul()->GetMeshRenderer()->GetMaterial()->SetInt(3, 1);


	EnableAndInitDashSmokeEffect();
}

void DashState::Exit()
{
	m_tDuration.Stop();
	m_pPlayer.lock()->GetRigidBody()->SetVelocity(AXIS::X, 0.f);
	m_pPlayer.lock()->GetActiveSkul()->GetMeshRenderer()->GetMaterial()->SetInt(3, 0);
}

void DashState::PlayAnimation()
{
	m_pPlayer.lock()->GetActiveSkul()->PlayAnimation(PLAYER_STATE::DASH, false);
}

void DashState::EnableAndInitAfterImage(weak_ptr<AfterImage> pAfterImage)
{
	pAfterImage.lock()->Enable();

	Vec3 vPlayerPos = Conv::PxVec3ToVec3(m_pPlayer.lock()->GetTransform()->GetPxTransform().p);
	const Vec3& vPlayerScale = m_pPlayer.lock()->GetActiveSkul()->GetTransform()->GetLocalScale();
	int32 iCurFrame = m_pPlayer.lock()->GetActiveSkul()->GetActiveAnimation().lock()->GetCurFrame();
	const FrameData& frameData = m_pPlayer.lock()->GetActiveSkul()->GetActiveAnimation().lock()->GetFrameDataList()[iCurFrame];
	const Vec2& vGlobalOffset = m_pPlayer.lock()->GetActiveSkul()->GetTransform()->GetGlobalOffset();

	pAfterImage.lock()->GetTransform()->SetGlobalOffset(vGlobalOffset);
	pAfterImage.lock()->GetTransform()->SetLocalPosition(vPlayerPos);
	pAfterImage.lock()->GetTransform()->SetLocalScale(vPlayerScale);
	pAfterImage.lock()->SetFrameData(frameData);
	pAfterImage.lock()->SetDirection(m_pPlayer.lock()->GetDirection());
}

void DashState::CreateAndAddAfterImagesToScene()
{
	shared_ptr<Scene> pActiveScene = GET_SINGLE(Scenes)->GetActiveScene();
	for (int32 i = 0; i < m_iAfterImageMaxCount; ++i)
	{
		shared_ptr<AfterImage> pAfterImage = make_shared<AfterImage>(AFTERIMAGE_TYPE::DASH);
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"AfterImage")->Clone();
		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();

		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pAfterImage->AddComponent(pMeshRenderer);
		pAfterImage->AddComponent(make_shared<Transform>());
		

		pAfterImage->AddComponent(make_shared<AfterImageDrawScript>(m_pPlayer.lock()));
		m_vAfterImages.push_back(pAfterImage);

		pAfterImage->Disable();
		pActiveScene->AddGameObject(pAfterImage);
	}
}

void DashState::EnableAndInitDashSmokeEffect()
{
	float fDistance = 70.f;
	uint8 iDirection = static_cast<uint8>(m_pPlayer.lock()->GetDirection());

	Vec3 vPlayerPos = Conv::PxVec3ToVec3(m_pPlayer.lock()->GetTransform()->GetPxTransform().p);
	const Vec3& vPlayerScale = m_pPlayer.lock()->GetActiveSkul()->GetTransform()->GetLocalScale();
	const Vec2& vGlobalOffset = m_pPlayer.lock()->GetActiveSkul()->GetTransform()->GetGlobalOffset();

	vPlayerPos.x += iDirection ? fDistance : -fDistance;
	vPlayerPos.y -= vPlayerScale.y / 2.f;

	m_pPlayer.lock()->GetDashSmokeEffect()->Enable();
	m_pPlayer.lock()->GetDashSmokeEffect()->GetTransform()->SetGlobalOffset(vGlobalOffset);
	m_pPlayer.lock()->GetDashSmokeEffect()->GetTransform()->SetLocalPosition(vPlayerPos);
	m_pPlayer.lock()->GetDashSmokeEffect()->SetDirection(m_pPlayer.lock()->GetDirection());
	m_pPlayer.lock()->GetDashSmokeEffect()->GetAnimator()->Play(L"DashSmoke_Small", false);
}
