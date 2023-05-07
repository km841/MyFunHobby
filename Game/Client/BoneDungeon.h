#pragma once
#include "Dungeon.h"
class BoneDungeon :
    public Dungeon
{
public:
	BoneDungeon(const wstring& szMapPath, const wstring& szScriptPath = L"");
	virtual ~BoneDungeon();

public:
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void FinalUpdate();

	virtual void Enter();
	virtual void Exit();
};

