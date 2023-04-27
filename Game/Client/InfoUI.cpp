#include "pch.h"
#include "InfoUI.h"

weak_ptr<InfoUI> InfoUI::s_pSelectedInfoUI;
InfoUI::InfoUI()
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
}

void InfoUI::LateUpdate()
{
	UI::LateUpdate();
}

void InfoUI::FinalUpdate()
{
	UI::FinalUpdate();
}
