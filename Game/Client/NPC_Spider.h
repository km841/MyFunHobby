#pragma once
#include "GameObject.h"
class NPC_Spider :
    public GameObject
{
public:
	NPC_Spider();
	virtual ~NPC_Spider();

public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();
};

