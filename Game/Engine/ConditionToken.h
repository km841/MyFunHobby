#pragma once
class ConditionToken
{
public:
	ConditionToken();
	~ConditionToken() = default;

public:
	FORCEINLINE bool GetState() { return m_bState; }
	FORCEINLINE void SetState(bool bState) { m_bState = bState; }

private:
	bool m_bState;
};

