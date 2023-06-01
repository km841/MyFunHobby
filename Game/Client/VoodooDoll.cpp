#include "pch.h"
#include "VoodooDoll.h"

VoodooDoll::VoodooDoll(const ItemInfo& itemInfo)
	: Item(itemInfo)
{
}

VoodooDoll::~VoodooDoll()
{
}

void VoodooDoll::Awake()
{
	Item::Awake();
}

void VoodooDoll::Start()
{
	Item::Start();
}

void VoodooDoll::Update()
{
	Item::Update();
}

void VoodooDoll::LateUpdate()
{
	Item::LateUpdate();
}

void VoodooDoll::FinalUpdate()
{
	Item::FinalUpdate();
}