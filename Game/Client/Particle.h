#pragma once
#include "GameObject.h"
class Particle :
    public GameObject
{
public:
	Particle();
	virtual ~Particle();

public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();

public:
	virtual void OnCollisionEnter(shared_ptr<GameObject> pGameObject);
	virtual void OnCollisionExit(shared_ptr<GameObject> pGameObject);

private:
	DECLARE_POOL(Particle);
};

