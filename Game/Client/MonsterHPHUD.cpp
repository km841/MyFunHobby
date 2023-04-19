#include "pch.h"
#include "MonsterHPHUD.h"

MonsterHPHUD::MonsterHPHUD(shared_ptr<Monster> pMonster)
	: MonsterHUD(pMonster)
{
}

MonsterHPHUD::~MonsterHPHUD()
{
}

void MonsterHPHUD::Awake()
{
	MonsterHUD::Awake();
}

void MonsterHPHUD::Start()
{
	MonsterHUD::Start();
}

void MonsterHPHUD::Update()
{
	MonsterHUD::Update();
}

void MonsterHPHUD::LateUpdate()
{
	MonsterHUD::LateUpdate();
}

void MonsterHPHUD::FinalUpdate()
{
	MonsterHUD::FinalUpdate();
}
