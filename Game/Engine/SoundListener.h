#pragma once
#include "Component.h"
class SoundListener :
    public Component
{
public:
	SoundListener();
	virtual ~SoundListener();

	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void FinalUpdate() override;
};

