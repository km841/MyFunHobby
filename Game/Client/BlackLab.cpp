#include "pch.h"
#include "BlackLab.h"
#include "Ch3BaseCamp.h"
#include "Ch3BossDungeon.h"
#include "Ch3ViceBossDungeon.h"
#include "Dungeon_Bone.h"
#include "Dungeon_Item.h"
#include "Dungeon_Gold.h"
#include "Dungeon_Shop.h"

BlackLab::BlackLab()
	: Stage(STAGE_KIND::BLACK_LAB)
{
}

BlackLab::~BlackLab()
{
}

void BlackLab::Awake()
{
	// Add dungeons
	AddDungeon(make_shared<Ch3BaseCamp>(L"..\\Resources\\Map\\Ch3BaseCampMap.map", L"..\\Resources\\Script\\ch3_basecamp_script.evtscript"), Vec4(-1450.f, 2000.f, 1800.f, -400.f));
	AddDungeon(make_shared<Dungeon_Shop>(L"..\\Resources\\Map\\Ch3ShopMap.map", L"..\\Resources\\Script\\ch3_shop1_script.evtscript"), Vec4(-650.f, 2000.f, 2200.f, -400.f));
	AddDungeon(make_shared<Dungeon_Gold>(L"..\\Resources\\Map\\Ch3Map2.map", L"..\\Resources\\Script\\ch3_script_2.evtscript"), Vec4(-1500.f, 2000.f, 3000.f, -400.f));
	AddDungeon(make_shared<Dungeon_Bone>(L"..\\Resources\\Map\\Ch3Map5.map", L"..\\Resources\\Script\\ch3_script_5.evtscript"), Vec4(-2050.f, 1500.f, 1000.f, -1500.f));
	AddDungeon(make_shared<Dungeon_Item>(L"..\\Resources\\Map\\Ch3Map4.map", L"..\\Resources\\Script\\ch3_script_4.evtscript"), Vec4(-1200.f, 2000.f, 1300.f, -1500.f));
	AddDungeon(make_shared<Dungeon_Shop>(L"..\\Resources\\Map\\Ch3ShopMap2.map", L"..\\Resources\\Script\\ch3_shop1_script.evtscript"), Vec4(-650.f, 2000.f, 2200.f, -400.f));
	AddDungeon(make_shared<Dungeon_Gold>(L"..\\Resources\\Map\\Ch3Map3.map", L"..\\Resources\\Script\\ch3_script_3.evtscript"), Vec4(-1500.f, 2000.f, 3800.f, -400.f));
	AddDungeon(make_shared<Ch3BossDungeon>(L"..\\Resources\\Map\\Ch3BossMap.map", L"..\\Resources\\Script\\ch3_bossmap_script.evtscript"), Vec4(-230.f, 930.f, 1400.f, -70.f));
	AddDungeon(make_shared<Ch3ViceBossDungeon>(L"..\\Resources\\Map\\Ch3ViceBossMap.map", L"..\\Resources\\Script\\ch3_vicebossmap_script.evtscript"), Vec4(-1000.f, 930.f, 2750.f, -700.f));

	// Awaken all stages and select the active dungeon.
	Stage::Awake();	
}

void BlackLab::Start()
{
	Stage::Start();
}

void BlackLab::Update()
{
	Stage::Update();
}

void BlackLab::LateUpdate()
{
	Stage::LateUpdate();
}

void BlackLab::FinalUpdate()
{
	Stage::FinalUpdate();
}

void BlackLab::Enter()
{
	Awake();
	m_pActiveDungeon.lock()->Enter();
}

void BlackLab::Exit()
{
	m_pActiveDungeon.lock()->Exit();
}
