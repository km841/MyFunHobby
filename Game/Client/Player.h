#pragma once
#include "GameObject.h"
class Player :
	public GameObject
{
public:
	Player();
	virtual ~Player();

public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();

private:
	


};

