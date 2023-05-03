#pragma once
#include "Stage.h"
class CitadelOfFate :
    public Stage
{
public:
	CitadelOfFate();
	virtual ~CitadelOfFate();

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void FinalUpdate() override;

	virtual void Enter() override;
	virtual void Exit() override;
};

