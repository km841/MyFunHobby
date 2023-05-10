#pragma once
#include "Dungeon.h"
class Dungeon_Item :
    public Dungeon
{
public:
	Dungeon_Item(const wstring& szMapPath, const wstring& szScriptPath = L"");
	virtual ~Dungeon_Item();

public:
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void FinalUpdate();

	virtual void Enter();
	virtual void Exit();
};

