#include "pch.h"
#include "Background.h"
#include "Scene.h"
#include "Player.h"
#include "RigidBody.h"
#include "Scenes.h"
#include "ComponentObject.h"
#include "Camera.h"
#include "Transform.h"
#include "Clock.h"
#include "Skul.h"

Background::Background()
	: GameObject(LAYER_TYPE::BACKGROUND)
{
}

Background::~Background()
{
}

void Background::Awake()
{
	GameObject::Awake();
}

void Background::Start()
{
	GameObject::Start();
}

void Background::Update()
{
	GameObject::Update();
	
	weak_ptr<Player> pPlayer = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer();

	if (!pPlayer.lock())
		return;

	if (Vec3::Zero == m_vPlayerPrevPos)
	{
		m_vPlayerPrevPos = pPlayer.lock()->GetActiveSkul()->GetTransform()->GetWorldPosition();
	}
	
	else
	{
		Vec3 vPlayerPos = pPlayer.lock()->GetActiveSkul()->GetTransform()->GetWorldPosition();
		Vec3 vDiff = vPlayerPos - m_vPlayerPrevPos;

		if (vDiff.Length() > 0.f)
		{
			float fInterpolationFactor = 0.2f;

			if (m_vFollowSpeed.x)
				vDiff.x /= m_vFollowSpeed.x;
			else
				vDiff.x = 0.f;

			if (m_vFollowSpeed.y)
				vDiff.y /= m_vFollowSpeed.y;
			else
				vDiff.y = 0.f;

			vDiff.y /= 2.f;
			const Vec3& vMyPos = GetTransform()->GetLocalPosition();
			Vec3 vTargetPosition = vMyPos + vDiff;
			Vec3 vInterpolatedPosition = vMyPos + (vTargetPosition - vMyPos) * fInterpolationFactor;
			GetTransform()->SetLocalPosition(vInterpolatedPosition);
		}

		m_vPlayerPrevPos = vPlayerPos;
	}
}

void Background::LateUpdate()
{
	GameObject::LateUpdate();
}

void Background::FinalUpdate()
{
	GameObject::FinalUpdate();
}
