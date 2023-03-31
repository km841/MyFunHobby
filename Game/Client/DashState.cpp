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
#include "Timer.h"
#include "AfterImage.h"
#include "Material.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Resources.h"
#include "AfterImageDrawScript.h"
#include "Scene.h"

DashState::DashState(shared_ptr<Player> pPlayer)
	: PlayerState(pPlayer)
	, m_tcDuration(0.2f)
	, m_fDashSpeed(1000.f)
	, m_iAfterImageMaxCount(4)
	, m_fAfterImageTimeOffset(0.25f)
{
}

void DashState::Awake()
{
	CreateAndAddAfterImagesToScene();
}

void DashState::Update()
{
	m_tcDuration.Update(DELTA_TIME);
	if (m_tcDuration.IsFinished())
	{
		AddChangeStateEvent(PLAYER_STATE::IDLE);
		return;
	}

	float fProgress = m_tcDuration.GetProgress();
	for (int32 i = 0; i < m_iAfterImageMaxCount; ++i)
	{
		if ((fProgress >= m_fAfterImageTimeOffset + (i * m_fAfterImageTimeOffset)) && !m_vAfterImages[i]->IsEnable())
		{
			EnableAndInitAfterImage(m_vAfterImages[i]);
		}
	}
}

void DashState::Enter()
{
	m_tcDuration.Start();

	m_pPlayer.lock()->GetAnimator()->Play(L"LittleBone_Dash", false);
	m_pPlayer.lock()->GetRigidBody()->RemoveGravity();
	m_pPlayer.lock()->GetRigidBody()->SetVelocity(AXIS::Y, 0.f);

	DIRECTION ePlayerDir = m_pPlayer.lock()->GetDirection();
	switch (ePlayerDir)
	{
	case DIRECTION::RIGHT:
		m_pPlayer.lock()->GetRigidBody()->SetVelocity(AXIS::X, m_fDashSpeed);
		break;
	case DIRECTION::LEFT:
		m_pPlayer.lock()->GetRigidBody()->SetVelocity(AXIS::X, -m_fDashSpeed);
		break;
	}
}

void DashState::Exit()
{
	m_tcDuration.Stop();
}

void DashState::EnableAndInitAfterImage(weak_ptr<AfterImage> pAfterImage)
{
	pAfterImage.lock()->Enable();

	Vec3 vPlayerPos = Conv::PxVec3ToVec3(m_pPlayer.lock()->GetTransform()->GetPxTransform().p);
	pAfterImage.lock()->GetTransform()->SetLocalPosition(vPlayerPos);

	const Vec3& vPlayerScale = m_pPlayer.lock()->GetTransform()->GetLocalScale();
	pAfterImage.lock()->GetTransform()->SetLocalScale(vPlayerScale);

	int32 iCurFrame = m_pPlayer.lock()->GetAnimator()->GetActiveAnimation()->GetCurFrame();
	const FrameData& frameData = m_pPlayer.lock()->GetAnimator()->GetActiveAnimation()->GetFrameDataList()[iCurFrame];

	pAfterImage.lock()->SetFrameData(frameData);
	pAfterImage.lock()->SetDirection(m_pPlayer.lock()->GetDirection());
}

void DashState::CreateAndAddAfterImagesToScene()
{
	shared_ptr<Scene> pActiveScene = GET_SINGLE(Scenes)->GetActiveScene();
	for (int32 i = 0; i < m_iAfterImageMaxCount; ++i)
	{
		shared_ptr<AfterImage> pAfterImage = AfterImage::Get();

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
