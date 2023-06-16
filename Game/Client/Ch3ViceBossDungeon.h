#pragma once
#include "Dungeon.h"
class Ch3ViceBossDungeon :
    public Dungeon
{
public:
	Ch3ViceBossDungeon(const wstring& szMapPath, const wstring& szScriptPath = L"");
	virtual ~Ch3ViceBossDungeon();

public:
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void FinalUpdate();

	virtual void Enter();
	virtual void Exit();
};

