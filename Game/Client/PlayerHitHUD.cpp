#include "pch.h"
#include "PlayerHitHUD.h"
#include "Animator.h"

PlayerHitHUD::PlayerHitHUD()
{
}

PlayerHitHUD::~PlayerHitHUD()
{
}

void PlayerHitHUD::Awake()
{
	HUD::Awake();
}

void PlayerHitHUD::Start()
{
	HUD::Start();
}

void PlayerHitHUD::Update()
{
	HUD::Update();
}

void PlayerHitHUD::LateUpdate()
{
	HUD::LateUpdate();
}

void PlayerHitHUD::FinalUpdate()
{
	HUD::FinalUpdate();
}

void PlayerHitHUD::PlayHitAnimation()
{
	GetAnimator()->Play(L"PlayerHit", false);
}