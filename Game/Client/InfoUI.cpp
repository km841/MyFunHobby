#include "pch.h"
#include "InfoUI.h"
#include "Scenes.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Texture.h"
#include "Input.h"
#include "Transform.h"
#include "ComponentObject.h"
#include "Resources.h"

weak_ptr<InfoUI> InfoUI::s_pSelectedInfoUI;
InfoUI::InfoUI(INFO_TYPE eInfoType)
	: m_eInfoType(eInfoType)
{
}

InfoUI::~InfoUI()
{
}

void InfoUI::Awake()
{
	UI::Awake();
}

void InfoUI::Start()
{
	UI::Start();
}

void InfoUI::Update()
{
	UI::Update();
	UpdateSelectedUI();
}

void InfoUI::LateUpdate()
{
	UI::LateUpdate();
}

void InfoUI::FinalUpdate()
{
	UI::FinalUpdate();
}

void InfoUI::Enable()
{
	GameObject::Enable();
}

void InfoUI::Disable()
{
	GameObject::Disable();
}

wstring InfoUI::GetGradeWstring(GRADE eGrade)
{
	switch (eGrade)
	{
	case GRADE::NORMAL:
		return L"노멀";
	case GRADE::RARE:
		return L"레어";
	case GRADE::UNIQUE:
		return L"유니크";
	case GRADE::REGENDARY:
		return L"레전더리";
	}

	assert(nullptr);
	return L"";
}

wstring InfoUI::GetSkulKindWstring(SKUL_KIND eSkulKind)
{
	switch (eSkulKind)
	{
	case SKUL_KIND::LITTLE_BONE:
		return L"리틀 본";
	case SKUL_KIND::HIGH_WARLOCK:
		return L"대마도사";
	}

	assert(nullptr);
	return L"";
}

wstring InfoUI::GetSkulTypeWstring(SKUL_TYPE eSkulType)
{
	switch (eSkulType)
	{
	case SKUL_TYPE::SPEED:
		return L"스피드";
	case SKUL_TYPE::BALANCE:
		return L"밸런스";
	case SKUL_TYPE::POWER:
		return L"파워";
	}

	assert(nullptr);
	return L"";
}

void InfoUI::UpdateSelectedUI()
{
	POINT vMousePos = GET_SINGLE(Input)->GetMousePos();
	shared_ptr<ComponentObject> pCamera = GET_SINGLE(Scenes)->GetActiveScene()->GetUICamera().lock();
	Vec3 vWorldPos = GET_SINGLE(Scenes)->ScreenToWorldPosition(Vec3(static_cast<float>(vMousePos.x), static_cast<float>(vMousePos.y), 10.f), pCamera->GetCamera());

	const Vec3& vMyPos = GetTransform()->GetWorldPosition();
	const Vec3& vMySize = GetTransform()->GetLocalScale();
	Vec3 vLeftTop = Vec3(vMyPos.x - vMySize.x, vMyPos.y + vMySize.y, vMyPos.z);
	Vec3 vRightBtm = Vec3(vMyPos.x + vMySize.x, vMyPos.y - vMySize.y, vMyPos.z);

	if (vWorldPos.x > vLeftTop.x && vWorldPos.x < vRightBtm.x &&
		vWorldPos.y > vRightBtm.y && vWorldPos.y < vLeftTop.y)
	{
		s_pSelectedInfoUI = Conv::BaseToDeclare<InfoUI>(shared_from_this());
	}

	if (s_pSelectedInfoUI.lock().get() == this)
	{
		if (!m_pSelectedTexture)
			m_pSelectedTexture = GET_SINGLE(Resources)->Load<Texture>(L"SelectedInfoUI", L"..\\Resources\\Texture\\UI\\Inventory\\Inventory_Select.png");
		GetMeshRenderer()->GetMaterial()->SetTexture(0, m_pSelectedTexture);

		// DetailInfo 작성 후 DetailInfo UI에게 전달
		ShowDetailInfo();

	}
	else
	{
		if (!m_pDeselectedTexture)
			m_pDeselectedTexture = GET_SINGLE(Resources)->Load<Texture>(L"DeselectedInfoUI", L"..\\Resources\\Texture\\UI\\Inventory\\Inventory_Deactivate.png");
		GetMeshRenderer()->GetMaterial()->SetTexture(0, m_pDeselectedTexture);
	}
}
