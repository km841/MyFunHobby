#include "pch.h"
#include "SealedSword.h"

SealedSword::SealedSword(const ItemInfo& itemInfo)
	: Item(itemInfo)
{
}

SealedSword::~SealedSword()
{
}

void SealedSword::Awake()
{
	Item::Awake();
}

void SealedSword::Start()
{
	Item::Start();
}

void SealedSword::Update()
{
	Item::Update();
}

void SealedSword::LateUpdate()
{
	Item::LateUpdate();
}

void SealedSword::FinalUpdate()
{
	Item::FinalUpdate();
}
