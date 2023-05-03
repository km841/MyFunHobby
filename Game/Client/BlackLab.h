#pragma once
#include "Stage.h"
class Dungeon;
class BlackLab :
    public Stage
{
public:
	BlackLab();
	virtual ~BlackLab();

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void FinalUpdate() override;

	virtual void Enter() override;
	virtual void Exit() override;

private:
	

};

