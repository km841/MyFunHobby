#pragma once
#include "GameObject.h"
class MagicSword :
    public GameObject
{
public:
	MagicSword(float fStayTime);
	virtual ~MagicSword();

public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();

private:
	Timer m_tStayTime;
	Timer m_tDuration;
	bool m_bActive;
	bool m_bDestroyed;
};

