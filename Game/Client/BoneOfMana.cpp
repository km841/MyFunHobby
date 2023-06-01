#include "pch.h"
#include "BoneOfMana.h"

BoneOfMana::BoneOfMana(const ItemInfo& itemInfo)
	: Item(itemInfo)
{
}

BoneOfMana::~BoneOfMana()
{
}

void BoneOfMana::Awake()
{
	Item::Awake();
}

void BoneOfMana::Start()
{
	Item::Start();
}

void BoneOfMana::Update()
{
	Item::Update();
}

void BoneOfMana::LateUpdate()
{
	Item::LateUpdate();
}

void BoneOfMana::FinalUpdate()
{
	Item::FinalUpdate();
}
