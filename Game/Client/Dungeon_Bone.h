#pragma once
#include "Dungeon.h"
class Dungeon_Bone :
    public Dungeon
{
public:
	Dungeon_Bone(const wstring& szMapPath, const wstring& szScriptPath = L"");
	virtual ~Dungeon_Bone();

public:
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void FinalUpdate();

	virtual void Enter();
	virtual void Exit();
};

