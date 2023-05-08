#pragma once
#include "BaseCamp.h"
class Ch3BaseCamp :
    public BaseCamp
{
public:
	Ch3BaseCamp(const wstring& szMapPath);
	virtual ~Ch3BaseCamp();

public:
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void FinalUpdate();

	virtual void Enter();
	virtual void Exit();
};

