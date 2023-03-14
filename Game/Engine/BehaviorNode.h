#pragma once

enum class BEHAVIOR_RESULT
{
	SUCCESS,
	RUNNING,
	FAILURE,
};

class BehaviorNode
{
public:
	BehaviorNode() = default;
	virtual ~BehaviorNode() { }

public:
	virtual BEHAVIOR_RESULT Run() = 0;
};