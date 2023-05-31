#include "pch.h"
#include "PlayerClubberShowScript.h"
#include "Scenes.h"
#include "Scene.h"
#include "Player.h"
#include "Engine.h"

PlayerClubberShowScript::PlayerClubberShowScript()
{
}

PlayerClubberShowScript::~PlayerClubberShowScript()
{
}

void PlayerClubberShowScript::LateUpdate()
{
	weak_ptr<Player> pPlayer = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer();

	if (!pPlayer.lock())
		return;

	Clobber& playerClobber = pPlayer.lock()->GetClobber();
	wstring szDarkHeart = std::to_wstring(playerClobber.iDarkHeart);
	wstring szBoneFragments = std::to_wstring(playerClobber.iBoneFragments);
	wstring szGold = std::to_wstring(playerClobber.iGold);
	wstring szDarkQuartz = std::to_wstring(playerClobber.iDarkQuartz);
	FONT->DrawString(szDarkHeart, 25.f, Vec3(1535.f, 195.f, 100.f), FONT_WEIGHT::BOLD, 0xffffffff, FONT_ALIGN::RIGHT);
	FONT->DrawString(szBoneFragments, 25.f, Vec3(1535.f, 150.f, 100.f), FONT_WEIGHT::BOLD, 0xffffffff, FONT_ALIGN::RIGHT);
	FONT->DrawString(szGold, 25.f, Vec3(1535.f, 105.f, 100.f), FONT_WEIGHT::BOLD, 0xffffffff, FONT_ALIGN::RIGHT);
	FONT->DrawString(szDarkQuartz, 25.f, Vec3(1535.f, 60.f, 100.f), FONT_WEIGHT::BOLD, 0xffffffff, FONT_ALIGN::RIGHT);
}
