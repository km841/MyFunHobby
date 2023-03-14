#pragma once
#include "GameObject.h"

class Monster :
    public GameObject
{
public:
	Monster();
	virtual ~Monster();

public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();

public:

private:



};

