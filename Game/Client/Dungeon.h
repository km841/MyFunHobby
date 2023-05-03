#pragma once
#include "Scene.h"
#include "Scenes.h"

class Dungeon
{
public:
	Dungeon(DUNGEON_TYPE eDungeonType, const wstring& szMapPath);
	virtual ~Dungeon();

public:
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void FinalUpdate();

	virtual void Enter() = 0;
	virtual void Exit() = 0;

protected:
	DUNGEON_TYPE m_eDungeonType;
	const wstring m_szMapPath;
};

