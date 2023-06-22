#include "pch.h"
#include "DropSkul.h"
#include "Transform.h"
#include "Clock.h"
#include "Input.h"
#include "Player.h"
#include "Scenes.h"
#include "Item.h"
#include "ObjectFactory.h"
#include "ObjectRemoveToSceneEvent.h"
#include "EventManager.h"
#include "InterfaceManager.h"
#include "Interface.h"
#include "ComponentObject.h"
#include "HUD.h"
#include "Cemetery.h"
#include "Skul.h"
#include "Engine.h"


DropSkul::DropSkul(SKUL_KIND eSkulKind)
	: GameObject(LAYER_TYPE::DROP_SKUL)
	, m_eSkulKind(eSkulKind)
	, m_bIsCollisionWithPlayer(false)
	, m_bFixed(false)
{
}

DropSkul::~DropSkul()
{
}

void DropSkul::Awake()
{
	GameObject::Awake();
	CreateDetailHUDAndAddedToScene();
}

void DropSkul::Start()
{
	GameObject::Start();
}

void DropSkul::Update()
{
	GameObject::Update();

	if (m_bIsCollisionWithPlayer)
	{
		weak_ptr<Player> pPlayer = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer();
		if (IS_DOWN(KEY_TYPE::F))
		{
			GET_SINGLE(Cemetery)->Get(m_eSkulKind)->Awake();
			shared_ptr<Skul> pDropSkul = pPlayer.lock()->ObtainSkul(GET_SINGLE(Cemetery)->Get(m_eSkulKind));
			CreateDropSkulAndAddedToScene(pDropSkul);

			// 스컬을 만들어서 다시 바닥에 떨어뜨린다.
			//pPlayer.lock()->EnableSwapActiveFlag();
			SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
			GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(m_pDetailHUD.lock(), eSceneType));
			GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(m_pVignetteHUD.lock(), eSceneType));
			GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(shared_from_this(), eSceneType));
		}

		m_pDetailHUD.lock()->Enable();
		m_pVignetteHUD.lock()->Enable();
		DrawItemDetail();
	}

	else
	{
		m_pDetailHUD.lock()->Disable();
		m_pVignetteHUD.lock()->Disable();
	}
}

void DropSkul::LateUpdate()
{
	GameObject::LateUpdate();
}

void DropSkul::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void DropSkul::Destroy()
{
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();

	if (m_pDetailHUD.lock())
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(m_pDetailHUD.lock(), eSceneType));

	if (m_pVignetteHUD.lock())
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(m_pVignetteHUD.lock(), eSceneType));
}

void DropSkul::CreateTouchEffectAddedToScene()
{
}

wstring DropSkul::GetSkulImage(SKUL_KIND eSkulKind)
{
	wstring szSkulImagePath = L"";
	switch (eSkulKind)
	{
	case SKUL_KIND::LITTLE_BONE:
		szSkulImagePath = L"..\\Resources\\Texture\\HUD\\LittleBone\\Image_LittleBone_Drop.png";
		break;
	case SKUL_KIND::HIGH_WARLOCK:
		szSkulImagePath = L"..\\Resources\\Texture\\HUD\\HighWarlock\\Image_HighWarlock_Drop.png";
		break;
	case SKUL_KIND::DEVIL_BERSERKER:
		szSkulImagePath = L"..\\Resources\\Texture\\HUD\\DevilBerserker\\Image_DevilBerserker_Drop.png";
		break;
	}

	return szSkulImagePath;
}

void DropSkul::OnCollisionEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::TILE == pGameObject->GetLayerType())
	{
		GetRigidBody()->SetLinearVelocityForDynamic(PxVec3(0.f, 0.f, 0.f));
		m_bFixed = true;
	}
}

void DropSkul::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
	{
		m_bIsCollisionWithPlayer = true;
	}
}

void DropSkul::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
	{
		m_bIsCollisionWithPlayer = false;
	}
}

void DropSkul::DrawItemDetail()
{
	Vec3 vStandard = m_pDetailHUD.lock()->GetTransform()->GetWorldPosition();
	const SkulInfo& skulInfo = GET_SINGLE(Cemetery)->GetSkulInfo(m_eSkulKind);
	{
		Vec3 vNamePos = vStandard;
		vNamePos.y += 87.5f;
		FONT->DrawStringAtWorldPos(skulInfo.szName, 23.f, vNamePos, FONT_WEIGHT::ULTRA_BOLD, NAME_COLOR, FONT_ALIGN::CENTER);
	}

	// Grade
	{
		Vec3 vGradePos = vStandard;
		vGradePos.x -= 180.f;
		vGradePos.y += 50.f;
		wstring szGrade = {};
		switch (skulInfo.eGrade)
		{
		case GRADE::NORMAL:
			szGrade = L"노멀";
			break;
		case GRADE::RARE:
			szGrade = L"레어";
			break;
		case GRADE::UNIQUE:
			szGrade = L"유니크";
			break;
		case GRADE::LEGENDARY:
			szGrade = L"레전더리";
			break;
		}
		FONT->DrawStringAtWorldPos(szGrade, 17.f, vGradePos, FONT_WEIGHT::ULTRA_BOLD, NAME_COLOR, FONT_ALIGN::CENTER);
	}

	// Comment
	{
		Vec3 vCommentPos = vStandard;
		vCommentPos.y += 20.f;
		FONT->DrawStringAtWorldPos(skulInfo.szComment, 17.f, vCommentPos, FONT_WEIGHT::BOLD, COMMENT_COLOR, FONT_ALIGN::CENTER);
	}
}

void DropSkul::CreateDetailHUDAndAddedToScene()
{
	shared_ptr<GameObject> pDetailHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<GameObject>(L"Forward", L"..\\Resources\\Texture\\HUD\\HUD_PopupItem_Ver2.png", LAYER_TYPE::UNKNOWN);
	pDetailHUD->GetTransform()->SetParent(GetTransform());
	pDetailHUD->GetTransform()->SetLocalPosition(Vec3(0.f, 200.f, 0.f));
	pDetailHUD->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pDetailHUD, eSceneType));
	m_pDetailHUD = pDetailHUD;

	shared_ptr<GameObject> pVignetteHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<GameObject>(L"Forward", L"", LAYER_TYPE::UNKNOWN);
	pVignetteHUD->GetTransform()->SetParent(pDetailHUD->GetTransform());
	pVignetteHUD->Awake();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pVignetteHUD, eSceneType));
	m_pVignetteHUD = pVignetteHUD;
}

void DropSkul::CreateDropSkulAndAddedToScene(shared_ptr<Skul> pSkul)
{
	shared_ptr<DropSkul> pGameObject = GET_SINGLE(ObjectFactory)->CreateObjectHasPhysical<DropSkul>(
		L"Forward", false, ACTOR_TYPE::DYNAMIC, GEOMETRY_TYPE::SPHERE, Vec3(50.f, 50.f, 1.f), MassProperties(), GetSkulImage(pSkul->GetSkulKind()), pSkul->GetSkulKind());
	Vec3 vSkulPos = GetTransform()->GetPhysicalPosition();
	vSkulPos.z -= 1;
	pGameObject->GetTransform()->SetLocalPosition(vSkulPos);

	PxVec3 vUpNormal = PxVec3(0.f, 1.f, 0.f);
	pGameObject->GetRigidBody()->SetLinearVelocityForDynamic(vUpNormal * 500.f);

	pGameObject->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pGameObject, eSceneType));
}

