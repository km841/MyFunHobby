#include "pch.h"
#include "InvisibleKnife.h"

InvisibleKnife::InvisibleKnife(const ItemInfo& itemInfo)
	: Item(itemInfo)
{
}

InvisibleKnife::~InvisibleKnife()
{
}

void InvisibleKnife::Awake()
{
	Item::Awake();
}

void InvisibleKnife::Start()
{
	Item::Start();
}

void InvisibleKnife::Update()
{
	Item::Update();
}

void InvisibleKnife::LateUpdate()
{
	Item::LateUpdate();
}

void InvisibleKnife::FinalUpdate()
{
	Item::FinalUpdate();
}
