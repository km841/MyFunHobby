#include "pch.h"
#include "Item.h"
#include "Texture.h"
#include "Resources.h"

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

std::vector<ITEM_KIND> Item::GetItemKindsOfGrade(GRADE eGrade)
{
	std::vector<ITEM_KIND> vItemKinds;
	int32 iStartIndex = 0;
	int32 iEndIndex = 0;
	switch (eGrade)
	{
	case GRADE::NORMAL:
		break;
	case GRADE::RARE:
		iStartIndex = 0;
		iEndIndex = ITEM_RARE_END;
		break;
	case GRADE::UNIQUE:
		iStartIndex = ITEM_RARE_END + 1;
		iEndIndex = ITEM_UNIQUE_END;
		break;
	case GRADE::LEGENDARY:
		iStartIndex = ITEM_UNIQUE_END + 1;
		iEndIndex = ITEM_LEGENDARY_END;
		break;
	}

	for (int32 i = iStartIndex; i < iEndIndex; ++i)
	{
		vItemKinds.push_back(static_cast<ITEM_KIND>(i));
	}

	return vItemKinds;
}

wstring Item::GetItemKindToDropItemPath(ITEM_KIND eItemKind)
{
	wstring szPath = {};

	switch (eItemKind)
	{
	case ITEM_KIND::INVISIBLE_KNIFE:
		szPath = L"..\\Resources\\Texture\\Item\\InvisibleKnife\\Image_InvisibleKnife.png";
		break;
	case ITEM_KIND::RING_OF_MOON:
		szPath = L"..\\Resources\\Texture\\Item\\RingOfMoon\\Image_RingOfMoon.png";
		break;
	case ITEM_KIND::SWORD_OF_SUN:
		szPath = L"..\\Resources\\Texture\\Item\\SwordOfSun\\Image_SwordOfSun.png";
		break;
	case ITEM_KIND::JENNYS_CHAIN_SICKLE:
		szPath = L"..\\Resources\\Texture\\Item\\JennysChainSickle\\Image_JennysChainSickle.png";
		break;
	case ITEM_KIND::THIEFS_BLACK_IRON_DAGGERS:
		szPath = L"..\\Resources\\Texture\\Item\\ThiefsBlackIronDaggers\\Image_ThiefsBlackIronDaggers.png";
		break;
	case ITEM_KIND::FORBIDDEN_SWORD:
		szPath = L"..\\Resources\\Texture\\Item\\ForbiddenSword\\Image_ForbiddenSword.png";
		break;
	case ITEM_KIND::RAVEN_LORDS_FEATHER:
		szPath = L"..\\Resources\\Texture\\Item\\RavenLordsFeather\\Image_RavenLordsFeather.png";
		break;
	case ITEM_KIND::VOODOO_DOLL:
		szPath = L"..\\Resources\\Texture\\Item\\VoodooDoll\\Image_VoodooDoll.png";
		break;
	case ITEM_KIND::EVIL_SWORD_KIRION:
		szPath = L"..\\Resources\\Texture\\Item\\EvilSwordKirion\\Image_EvilSwordKirion.png";
		break;
	case ITEM_KIND::BONE_OF_MANA:
		szPath = L"..\\Resources\\Texture\\Item\\BoneOfMana\\Image_BoneOfMana.png";
		break;
	case ITEM_KIND::GUNPOWDER_SWORD:
		szPath = L"..\\Resources\\Texture\\Item\\GunpowderSword\\Image_GunpowderSword.png";
		break;
	case ITEM_KIND::BRIGHT_DAWN:
		szPath = L"..\\Resources\\Texture\\Item\\BrightDawn\\Image_BrightDawn.png";
		break;

	}
	assert(!szPath.empty());
	return szPath;
}
