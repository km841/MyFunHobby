#include "pch.h"
#include "DetailInfoUI.h"
#include "InfoUI.h"
#include "Font.h"
#include "InventoryUI.h"
#include "Resources.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "SkulInfoUI.h"
#include "Transform.h"
#include "Texture.h"
#include "Engine.h"
#include "ObjectFactory.h"
#include "Scene.h"
#include "Scenes.h"
#include "Engrave.h"

DetailInfoUI::DetailInfoUI()
	:m_DetailInfo{}
{
}

DetailInfoUI::~DetailInfoUI()
{
}

void DetailInfoUI::Awake()
{
	UI::Awake();
	CreateDetailSubUIAndAddedToScene();
}

void DetailInfoUI::Start()
{
	UI::Start();
}

void DetailInfoUI::Update()
{
	UI::Update();
	if (m_pInventoryUI.lock()->IsEnable())
	{
		if (m_DetailInfo.bUse)
		{
			switch (m_DetailInfo.eInfoType)
			{
			case INFO_TYPE::SKUL_INFO:
				DrawSkulInfo();
				break;

			case INFO_TYPE::ITEM_INFO:
				DrawItemInfo();
				break;

			case INFO_TYPE::ESSENCE_INFO:
				DrawEssenceInfo();
				break;

			case INFO_TYPE::DARKABIL_INFO:
				DrawDarkAbilInfo();
				break;
			}
		}
	}


}

void DetailInfoUI::LateUpdate()
{
	UI::LateUpdate();
}

void DetailInfoUI::FinalUpdate()
{
	UI::FinalUpdate();
}

void DetailInfoUI::Enable()
{
	GameObject::Enable();
	m_pVignetteUI->Enable();
	m_pFirstImageUI->Enable();
	m_pSecondImageUI->Enable();
}

void DetailInfoUI::Disable()
{
	m_pVignetteUI->Disable();
	m_pFirstImageUI->Disable();
	m_pSecondImageUI->Disable();
	GameObject::Disable();
}

void DetailInfoUI::DrawSkulInfo()
{
	SetSkulDetailTexture();
	InitSkulDetailSubUI();

	// Enum To Wstring
	FONT->DrawString(m_DetailInfo.skulInfo.GradeEnumToWstring(), 20.f, Vec3(775.f, 670.f, 0.f), FONT_WEIGHT::ULTRA_BOLD, GRADE_COLOR);
	FONT->DrawString(m_DetailInfo.skulInfo.SkulTypeEnumToWstring(), 20.f, Vec3(1375.f, 670.f, 0.f), FONT_WEIGHT::ULTRA_BOLD, GRADE_COLOR);
	FONT->DrawString(m_DetailInfo.skulInfo.SkulKindEnumToWstring(), 25.f, Vec3(1076.f, 685.f, 0.f), FONT_WEIGHT::ULTRA_BOLD, NAME_COLOR);

	FONT->DrawString(m_DetailInfo.skulInfo.szComment, 20.f, Vec3(1076.f, 550.f, 0.f), FONT_WEIGHT::ULTRA_BOLD, COMMENT_COLOR);
}

void DetailInfoUI::DrawItemInfo()
{
	SetItemDetailTexture();
	InitItemDetailSubUI();

	FONT->DrawString(m_DetailInfo.itemInfo.GradeEnumToWstring(), 20.f, Vec3(775.f, 670.f, 0.f), FONT_WEIGHT::ULTRA_BOLD, GRADE_COLOR);
	FONT->DrawString(m_DetailInfo.itemInfo.szName, 25.f, Vec3(1076.f, 685.f, 0.f), FONT_WEIGHT::ULTRA_BOLD, NAME_COLOR);

	FONT->DrawString(m_DetailInfo.itemInfo.szComment, 20.f, Vec3(1076.f, 623.f, 0.f), FONT_WEIGHT::ULTRA_BOLD, COMMENT_COLOR);
	FONT->DrawString(m_DetailInfo.itemInfo.szExplanation, 20.f, Vec3(1076.f, 500.f, 0.f), FONT_WEIGHT::ULTRA_BOLD, COMMENT_COLOR);

	FONT->DrawString(m_DetailInfo.itemInfo.pFirstEngrave->GetName(), 20.f, Vec3(878.f, 135.f, 0.f), FONT_WEIGHT::ULTRA_BOLD, NAME_COLOR);
	FONT->DrawString(m_DetailInfo.itemInfo.pSecondEngrave->GetName(), 20.f, Vec3(1274.f, 135.f, 0.f), FONT_WEIGHT::ULTRA_BOLD, NAME_COLOR);
}

void DetailInfoUI::DrawEssenceInfo()
{
	FONT->DrawString(L"ArtifactInfo", 20.f, Vec3(16.f, 16.f, 0.f));
}

void DetailInfoUI::DrawDarkAbilInfo()
{
	FONT->DrawString(L"DarkAbilInfo", 20.f, Vec3(16.f, 16.f, 0.f));
}

void DetailInfoUI::SetSkulDetailTexture()
{
	shared_ptr<Texture> pTexture = nullptr;

	switch (m_DetailInfo.eTotalSkills)
	{
	case SKILL_INDEX::FIRST:
		pTexture = GET_SINGLE(Resources)->Load<Texture>(L"SkulInfoDetail_1Skill", L"..\\Resources\\Texture\\UI\\Inventory\\Image_Skill01_Frame.png");
		break;
	case SKILL_INDEX::SECOND:
		pTexture = GET_SINGLE(Resources)->Load<Texture>(L"SkulInfoDetail_2Skill", L"..\\Resources\\Texture\\UI\\Inventory\\Image_Skill02_Frame.png");
		break;
	}

	assert(pTexture);
	GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture);
	GetTransform()->SetLocalScale(pTexture->GetTexSize());
}

void DetailInfoUI::InitSkulDetailSubUI()
{
	m_pVignetteUI->GetMeshRenderer()->GetMaterial()->SetTexture(0, m_DetailInfo.skulInfo.pVignetteTexture);
	m_pVignetteUI->GetTransform()->SetLocalScale(m_DetailInfo.skulInfo.pVignetteTexture->GetTexSize());
	m_pVignetteUI->GetTransform()->SetGlobalOffset(m_DetailInfo.skulInfo.vVignetteTextureOffset);

	const SkillInfo& FirstSkillInfo = m_DetailInfo.skulInfo.FirstSkillInfo;
	const SkillInfo& SecondSkillInfo = m_DetailInfo.skulInfo.SecondSkillInfo;
	const SkillInfo& SwapSkillInfo = m_DetailInfo.skulInfo.SwapSkillInfo;
	
	FONT->DrawString(SwapSkillInfo.szName, 20.f, Vec3(1076.f, 263.f, 0.f), FONT_WEIGHT::ULTRA_BOLD, NAME_COLOR);

	SKILL_INDEX eTotalSkills = m_DetailInfo.eTotalSkills;
	switch (eTotalSkills)
	{
	case SKILL_INDEX::FIRST:
		m_pFirstImageUI->GetMeshRenderer()->GetMaterial()->SetTexture(0, FirstSkillInfo.pSkillTexture);
		m_pSecondImageUI->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr);
		m_pFirstImageUI->GetTransform()->SetLocalScale(Vec3(25.f, 25.f, 1.f));
		m_pFirstImageUI->GetTransform()->SetLocalPosition(Vec3(0.f, -146.f, -10.f));
		FONT->DrawString(FirstSkillInfo.szName, 20.f, Vec3(1076.f, 133.f, 0.f), FONT_WEIGHT::ULTRA_BOLD, NAME_COLOR);
		break;
	case SKILL_INDEX::SECOND:
		m_pFirstImageUI->GetMeshRenderer()->GetMaterial()->SetTexture(0, FirstSkillInfo.pSkillTexture);
		m_pFirstImageUI->GetTransform()->SetLocalScale(Vec3(27.f, 27.f, 1.f));
		m_pSecondImageUI->GetMeshRenderer()->GetMaterial()->SetTexture(0, SecondSkillInfo.pSkillTexture);
		m_pSecondImageUI->GetTransform()->SetLocalScale(Vec3(27.f, 27.f, 1.f));
		break;
	}
}

void DetailInfoUI::SetItemDetailTexture()
{
	shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"ItemInfoDetail", L"..\\Resources\\Texture\\UI\\Inventory\\Image_Item_Frame.png");
	assert(pTexture);
	GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture);
	GetTransform()->SetLocalScale(pTexture->GetTexSize());
}

void DetailInfoUI::InitItemDetailSubUI()
{
	m_pVignetteUI->GetMeshRenderer()->GetMaterial()->SetTexture(0, m_DetailInfo.itemInfo.pVignetteTexture);
	m_pVignetteUI->GetTransform()->SetLocalScale(m_DetailInfo.itemInfo.pVignetteTexture->GetTexSize());
	m_pVignetteUI->GetTransform()->SetGlobalOffset(Vec2(0.f, 0.f));
	ENGRAVE eFirstEng = m_DetailInfo.itemInfo.pFirstEngrave->GetEngrave();
	ENGRAVE eSecondEng = m_DetailInfo.itemInfo.pSecondEngrave->GetEngrave();

	m_pFirstImageUI->GetMeshRenderer()->GetMaterial()->SetTexture(0, Engrave::GetEngraveTexture(eFirstEng, ENGRAVE_STATE::ACTIVATE));
	m_pSecondImageUI->GetMeshRenderer()->GetMaterial()->SetTexture(0, Engrave::GetEngraveTexture(eSecondEng, ENGRAVE_STATE::ACTIVATE));

	m_pFirstImageUI->GetTransform()->SetLocalPosition(Vec3(-157.5f, -146.5f, -10.f));
	m_pFirstImageUI->GetTransform()->SetLocalScale(Vec3(24.f, 24.f, 1.f));

	m_pSecondImageUI->GetTransform()->SetLocalPosition(Vec3(157.5f, -146.5f, -10.f));
	m_pSecondImageUI->GetTransform()->SetLocalScale(Vec3(24.f, 24.f, 1.f));
}

void DetailInfoUI::CreateDetailSubUIAndAddedToScene()
{
	// Create Vignette UI
	{
		m_pVignetteUI = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<UI>(L"Forward");
		m_pVignetteUI->GetTransform()->SetParent(GetTransform());
		m_pVignetteUI->GetTransform()->SetLocalPosition(Vec3(-1.f, 330.f, -10.f));

		m_pVignetteUI->Awake();
		m_pVignetteUI->Disable();
		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(m_pVignetteUI, eSceneType));
	}

	// Create First Image UI
	{
		m_pFirstImageUI= GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<UI>(L"Forward");
		m_pFirstImageUI->GetTransform()->SetParent(GetTransform());
		m_pFirstImageUI->GetTransform()->SetLocalPosition(Vec3(0.f, -146.f, -10.f));
		m_pFirstImageUI->GetTransform()->SetLocalScale(Vec3(27.f, 27.f, 1.f));

		m_pFirstImageUI->Awake();
		m_pFirstImageUI->Disable();
		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(m_pFirstImageUI, eSceneType));
	}

	// Create Second Image UI
	{
		m_pSecondImageUI = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<UI>(L"Forward");
		m_pSecondImageUI->GetTransform()->SetParent(GetTransform());
		m_pSecondImageUI->GetTransform()->SetLocalPosition(Vec3(30.f, 0.f, -10.f));
		m_pSecondImageUI->GetTransform()->SetLocalScale(Vec3(27.f, 27.f, 1.f));

		m_pSecondImageUI->Awake();
		m_pSecondImageUI->Disable();
		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(m_pSecondImageUI, eSceneType));
	}

}
