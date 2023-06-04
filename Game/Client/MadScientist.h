#pragma once
#include "GameObject.h"
class MadScientist :
    public GameObject
{
public:
	MadScientist();
	virtual ~MadScientist();

public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();
};

