#pragma once
#include "Dungeon.h"
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
};

