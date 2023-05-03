#pragma once
#include "Dungeon.h"
class BaseCamp :
    public Dungeon
{
public:
	BaseCamp(const wstring& szMapPath);
	virtual ~BaseCamp();

public:
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void FinalUpdate();

	virtual void Enter();
	virtual void Exit();

private:
	
};

