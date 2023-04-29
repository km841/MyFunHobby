#include "pch.h"
#include "Item.h"

Item::Item(const ItemInfo& itemInfo)
	: Object(OBJECT_TYPE::ITEM)
	, m_ItemInfo(itemInfo)
{
}

Item::~Item()
{
}

void Item::Awake()
{
}

void Item::Start()
{
}

void Item::Update()
{
}

void Item::LateUpdate()
{
}

void Item::FinalUpdate()
{
}
