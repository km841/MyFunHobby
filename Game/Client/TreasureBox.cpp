#include "pch.h"
#include "TreasureBox.h"

TreasureBox::TreasureBox(GRADE eGrade)
	: MapReward(eGrade)
{
}

TreasureBox::~TreasureBox()
{
}

void TreasureBox::Awake()
{
	MapReward::Awake();
}

void TreasureBox::Start()
{
	MapReward::Start();
}

void TreasureBox::Update()
{
	MapReward::Update();
}

void TreasureBox::LateUpdate()
{
	MapReward::LateUpdate();
}

void TreasureBox::FinalUpdate()
{
	MapReward::FinalUpdate();
}
