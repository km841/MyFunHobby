#pragma once
#include "BehaviorComposite.h"

// �ڽ� ��� �� �ϳ��� Success�� ��ȯ�ϸ� �ٷ� Success�� ��ȯ�Ѵ�
// OR ����Ʈ�� ���� ����
class Selector
	: public BehaviorComposite
{
public:
	Selector() = default;
	virtual ~Selector() { }

public:
	virtual BEHAVIOR_RESULT Run() override;


private:


};