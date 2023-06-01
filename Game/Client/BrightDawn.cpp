#include "pch.h"
#include "BrightDawn.h"

BrightDawn::BrightDawn(const ItemInfo& itemInfo)
	: Item(itemInfo)
{
}

BrightDawn::~BrightDawn()
{
}

void BrightDawn::Awake()
{
	Item::Awake();
}

void BrightDawn::Start()
{
	Item::Start();
}

void BrightDawn::Update()
{
	Item::Update();
}

void BrightDawn::LateUpdate()
{
	Item::LateUpdate();
}

void BrightDawn::FinalUpdate()
{
	Item::FinalUpdate();
}