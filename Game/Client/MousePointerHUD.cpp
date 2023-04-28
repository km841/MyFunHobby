#include "pch.h"
#include "MousePointerHUD.h"
#include "Transform.h"
#include "Scene.h"
#include "Scenes.h"
#include "Input.h"
#include "ComponentObject.h"
#include "Font.h"

MousePointerHUD::MousePointerHUD()
{
}

MousePointerHUD::~MousePointerHUD()
{
}

void MousePointerHUD::Awake()
{
	HUD::Awake();
}

void MousePointerHUD::Start()
{
	HUD::Start();
}

void MousePointerHUD::Update()
{
	HUD::Update();
	POINT vMousePos = GET_SINGLE(Input)->GetMousePos();
	shared_ptr<ComponentObject> pCamera = GET_SINGLE(Scenes)->GetActiveScene()->GetUICamera().lock();
	Vec3 vWorldPos = GET_SINGLE(Scenes)->ScreenToWorldPosition(
		Vec3(static_cast<float>(vMousePos.x), static_cast<float>(vMousePos.y), 10.f), pCamera->GetCamera());
	vWorldPos.x += 10.f;
	vWorldPos.y -= 5.f;
	GetTransform()->SetLocalPosition(vWorldPos);
}

void MousePointerHUD::LateUpdate()
{
	HUD::LateUpdate();
}

void MousePointerHUD::FinalUpdate()
{
	HUD::FinalUpdate();
}
