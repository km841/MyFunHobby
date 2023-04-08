#pragma once
#include "Skul.h"
class HighWarlock :
    public Skul
{
public:
	HighWarlock();
	virtual ~HighWarlock() = default;

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void FinalUpdate() override;

private:

};

