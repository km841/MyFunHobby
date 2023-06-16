#pragma once
#include "Monster.h"
class VeteranHero :
    public Monster
{
public:
	VeteranHero();
	virtual ~VeteranHero();

public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();

};

