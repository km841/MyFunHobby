#pragma once
#include "PlayerState.h"
class PathState :
    public PlayerState
{
public:
	explicit PathState(shared_ptr<Player> pPlayer);
	virtual ~PathState() = default;

public:
	virtual void Update() override;

public:
	virtual void Enter() override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;
};

