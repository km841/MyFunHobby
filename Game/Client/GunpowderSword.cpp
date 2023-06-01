#include "pch.h"
#include "GunpowderSword.h"
GunpowderSword::GunpowderSword(const ItemInfo& itemInfo)
	: Item(itemInfo)
{
}

GunpowderSword::~GunpowderSword()
{
}

void GunpowderSword::Awake()
{
	Item::Awake();
}

void GunpowderSword::Start()
{
	Item::Start();
}

void GunpowderSword::Update()
{
	Item::Update();
}

void GunpowderSword::LateUpdate()
{
	Item::LateUpdate();
}

void GunpowderSword::FinalUpdate()
{
	Item::FinalUpdate();
}
