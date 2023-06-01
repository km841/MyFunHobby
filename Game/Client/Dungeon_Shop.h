#pragma once
#include "Dungeon.h"
#define EXHIBITION_ITEM_COUNT 4
class ExhibitionItem;
class Dungeon_Shop :
    public Dungeon
{
public:
	Dungeon_Shop(const wstring& szMapPath, const wstring& szScriptPath = L"");
	virtual ~Dungeon_Shop();

public:
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void FinalUpdate();

	virtual void Enter();
	virtual void Exit();

	void RenderExhibitionItemPrice();

	void CreateItemToPath();
	void RenewShopItemList();
	std::vector<weak_ptr<ExhibitionItem>> m_vExhibitionItemList;
	std::map<ITEM_KIND, wstring> m_mItemToPath;
};

