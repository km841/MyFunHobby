#pragma once
#include "Dungeon.h"
class Dungeon_Gold :
    public Dungeon
{
public:
	Dungeon_Gold(const wstring& szMapPath, const wstring& szScriptPath = L"");
	virtual ~Dungeon_Gold();

public:
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void FinalUpdate();

	virtual void Enter();
	virtual void Exit();
};

