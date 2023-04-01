#pragma once
#include "SkulSkill.h"
class SkullThrow :
    public SkulSkill
{
public:
	SkullThrow();
	virtual ~SkullThrow() = default;

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void FinalUpdate() override;
};

