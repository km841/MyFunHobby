#include "pch.h"
#include "CreateMapRewardEvent.h"
#include "MapReward.h"
#include "Scenes.h"
#include "Scene.h"
#include "ObjectFactory.h"
#include "Resources.h"
#include "AnimationLocalEffect.h"
#include "Transform.h"
#include "ObjectAddedToSceneEvent.h"
#include "TreasureBox.h"
#include "DungeonWall.h"
#include "Animation.h"
#include "Animator.h"
#include "BoneReward.h"

CreateMapRewardEvent::CreateMapRewardEvent(shared_ptr<ConditionBlock> pConditionBlock, GRADE eGrade, DUNGEON_TYPE eDungeonType)
	: DungeonEvent(DUNGEON_EVENT_KIND::CREATE_MAP_REWARD, pConditionBlock)
	, m_eGrade(eGrade)
	, m_eDungeonType(eDungeonType)
{
}

CreateMapRewardEvent::~CreateMapRewardEvent()
{
}

void CreateMapRewardEvent::Update()
{
	DungeonEvent::Update();
}

void CreateMapRewardEvent::ExecuteEvent()
{
	auto& vGameObjects = GET_SINGLE(Scenes)->GetActiveScene()->GetGameObjects(LAYER_TYPE::DUNGEON_WALL);
	assert(!vGameObjects.empty());

	static_pointer_cast<DungeonWall>(vGameObjects[0])->SetDungeonClearFlag();
	const Vec3& vWallPos = vGameObjects[0]->GetTransform()->GetLocalPosition();

	shared_ptr<MapReward> pMapReward = nullptr;
	switch (m_eDungeonType)
	{
	case DUNGEON_TYPE::DUNGEON_ITEM:
		pMapReward = CreateItemReward(vWallPos);
		break;
	case DUNGEON_TYPE::DUNGEON_GOLD:
		pMapReward = CreateGoldReward(vWallPos);
		break;
	case DUNGEON_TYPE::DUNGEON_BONE:
		pMapReward = CreateBoneReward(vWallPos);
		break;
	case DUNGEON_TYPE::VICE_BOSS:
		break;
	case DUNGEON_TYPE::STAGE_BOSS:
		break;
	}
	
	// Create Local Animation!
	CreateRewardEffectAddedToScene(vWallPos);

	pMapReward->Awake();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pMapReward, SCENE_TYPE::DUNGEON));
}

shared_ptr<MapReward> CreateMapRewardEvent::CreateItemReward(const Vec3& vPos)
{
	wstring szResourcePath = L"..\\Resources\\Texture\\Sprites\\Dungeon\\MapReward\\TreasureBox\\";
	wstring szTexPath = {};
	Vec3 vBoxPos = vPos;
	// 초기 이미지는 닫힌 이미지

	wstring szOpenAnimPath = {};
	switch (m_eGrade)
	{
	case GRADE::NORMAL:
		szTexPath = szResourcePath + L"Image_TreasureBox_Normal.png";
		vBoxPos.y = vPos.y - 73.f;
		szOpenAnimPath = L"..\\Resources\\Animation\\Dungeon\\MapReward\\treasure_box_normal_open.anim";
		break;
	case GRADE::RARE:
		szTexPath = szResourcePath + L"Image_TreasureBox_Rare.png";
		vBoxPos.y = vPos.y - 71.f;
		szOpenAnimPath = L"..\\Resources\\Animation\\Dungeon\\MapReward\\treasure_box_rare_open.anim";
		break;
	case GRADE::UNIQUE:
		szTexPath = szResourcePath + L"Image_TreasureBox_Unique.png";
		vBoxPos.y = vPos.y - 64.f;
		szOpenAnimPath = L"..\\Resources\\Animation\\Dungeon\\MapReward\\treasure_box_unique_open.anim";
		break;
	case GRADE::LEGENDARY:
		szTexPath = szResourcePath + L"Image_TreasureBox_Legendary.png";
		vBoxPos.y = vPos.y - 57.f;
		szOpenAnimPath = L"..\\Resources\\Animation\\Dungeon\\MapReward\\treasure_box_Legendary_open.anim";
		break;
	}

	shared_ptr<TreasureBox> pTreasureBox = GET_SINGLE(ObjectFactory)->CreateObjectHasPhysical<TreasureBox>(L"Deferred", false,
		ACTOR_TYPE::STATIC, GEOMETRY_TYPE::BOX, Vec3(30.f, 30.f, 1.f), MassProperties(), szTexPath, m_eGrade);

	pTreasureBox->AddComponent(make_shared<Animator>());
	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"TreasureBox_Open", szOpenAnimPath);
	assert(pAnimation);

	pTreasureBox->GetAnimator()->AddAnimation(L"TreasureBox_Open", pAnimation);

	vBoxPos.z = vPos.z - 1.f;
	pTreasureBox->GetTransform()->SetLocalPosition(vBoxPos);

	return pTreasureBox;
}

shared_ptr<MapReward> CreateMapRewardEvent::CreateGoldReward(const Vec3& vPos)
{
	return shared_ptr<MapReward>();
}

shared_ptr<MapReward> CreateMapRewardEvent::CreateBoneReward(const Vec3& vPos)
{
	wstring szResourcePath = L"..\\Resources\\Texture\\Sprites\\Dungeon\\MapReward\\BoneReward\\";
	wstring szTexPath = {};
	Vec3 vBonePos = vPos;

	wstring szDeactivateAnimPath = {};
	switch (m_eGrade)
	{
	case GRADE::NORMAL:
		szTexPath = szResourcePath + L"Image_BoneReward_Normal.png";
		vBonePos.y = vPos.y - 60.f;
		szDeactivateAnimPath = L"..\\Resources\\Animation\\Dungeon\\MapReward\\bone_reward_normal_deactivate.anim";
		break;
	case GRADE::RARE:
		szTexPath = szResourcePath + L"Image_BoneReward_Rare.png";
		vBonePos.y = vPos.y - 64.f;
		szDeactivateAnimPath = L"..\\Resources\\Animation\\Dungeon\\MapReward\\bone_reward_rare_deactivate.anim";
		break;
	case GRADE::UNIQUE:
		szTexPath = szResourcePath + L"Image_BoneReward_Unique.png";
		vBonePos.y = vPos.y;
		szDeactivateAnimPath = L"..\\Resources\\Animation\\Dungeon\\MapReward\\bone_reward_unique_deactivate.anim";
		break;
	case GRADE::LEGENDARY:
		szTexPath = szResourcePath + L"Image_BoneReward_Legendary.png";
		vBonePos.y = vPos.y + 40.f;
		szDeactivateAnimPath = L"..\\Resources\\Animation\\Dungeon\\MapReward\\bone_reward_legendary_deactivate.anim";
		break;
	}

	shared_ptr<BoneReward> pBoneReward = GET_SINGLE(ObjectFactory)->CreateObjectHasPhysical<BoneReward>(L"Deferred", false,
		ACTOR_TYPE::STATIC, GEOMETRY_TYPE::BOX, Vec3(30.f, 100.f, 1.f), MassProperties(), szTexPath, m_eGrade);

	pBoneReward->AddComponent(make_shared<Animator>());
	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Deactivate_Bone", szDeactivateAnimPath);
	assert(pAnimation);
	pBoneReward->GetAnimator()->AddAnimation(L"Deactivate_Bone", pAnimation);

	vBonePos.z = vPos.z - 1.f;
	pBoneReward->GetTransform()->SetLocalPosition(vBonePos);

	return pBoneReward;
}

void CreateMapRewardEvent::CreateRewardEffectAddedToScene(const Vec3& vPos)
{
	shared_ptr<AnimationLocalEffect> pEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<AnimationLocalEffect>(L"Forward");
	Vec3 pEffectPos = vPos;
	pEffectPos.y = vPos.y + 120.f;
	pEffectPos.z = vPos.z - 3.f;
	pEffect->GetTransform()->SetLocalPosition(pEffectPos);

	pEffect->AddComponent(make_shared<Animator>());

	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"DungeonRewardEffect", L"..\\Resources\\Animation\\Dungeon\\MapReward\\dungeon_map_reward.anim");
	pEffect->GetAnimator()->AddAnimation(L"DungeonRewardEffect", pAnimation);
	pEffect->GetAnimator()->Play(L"DungeonRewardEffect", false);

	pEffect->Awake();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pEffect, SCENE_TYPE::DUNGEON));

}
