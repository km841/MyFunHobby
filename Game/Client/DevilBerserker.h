#pragma once
#include "Skul.h"
class DevilBerserker :
    public Skul
{
public:
	DevilBerserker(const SkulInfo& skulInfo);
	virtual ~DevilBerserker() = default;

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void FinalUpdate() override;

private:
	BERSERKER_STATE m_eBerserkerState;
};

