#pragma once
#include "Skul.h"
class LittleBone :
    public Skul
{
public:
	LittleBone();
	virtual ~LittleBone() = default;

public:
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void FinalUpdate() override;

public:
	FORCEINLINE bool HasHead() { return m_bHasHead; }

public:
	bool m_bHasHead;
};

