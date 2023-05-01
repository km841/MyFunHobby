#include "pch.h"
#include "ForbiddenSword.h"

ForbiddenSword::ForbiddenSword(const ItemInfo& itemInfo)
	: Item(itemInfo)
{
}

ForbiddenSword::~ForbiddenSword()
{
}

void ForbiddenSword::Awake()
{
	Item::Awake();
}

void ForbiddenSword::Start()
{
	Item::Start();
}

void ForbiddenSword::Update()
{
	Item::Update();
}

void ForbiddenSword::LateUpdate()
{
	Item::LateUpdate();
}

void ForbiddenSword::FinalUpdate()
{
	Item::FinalUpdate();
}
