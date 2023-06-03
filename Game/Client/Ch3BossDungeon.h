#pragma once
#include "Dungeon.h"
class Ch3BossDungeon
	: public Dungeon
{
public:
	Ch3BossDungeon(const wstring& szMapPath, const wstring& szScriptPath = L"");
	virtual ~Ch3BossDungeon();

public:
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void FinalUpdate();
};

