#include "pch.h"
#include "RingOfMoon.h"

RingOfMoon::RingOfMoon(const ItemInfo& itemInfo)
	: Item(itemInfo)
{
}

RingOfMoon::~RingOfMoon()
{
}

void RingOfMoon::Awake()
{
	Item::Awake();
}

void RingOfMoon::Start()
{
	Item::Start();
}

void RingOfMoon::Update()
{
	Item::Update();
}

void RingOfMoon::LateUpdate()
{
	Item::LateUpdate();
}

void RingOfMoon::FinalUpdate()
{
	Item::FinalUpdate();
}

