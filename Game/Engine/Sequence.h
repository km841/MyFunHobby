#pragma once
#include "BehaviorComposite.h"

// �ڽ� ��� �� �ϳ��� Failure�� ��ȯ�ϸ� �ٷ� Failure�� ��ȯ�Ѵ�
// AND ����Ʈ�� ���� ����
class Sequence
	: public BehaviorComposite
{
public:
	Sequence() = default;
	virtual ~Sequence() { }

public:
	virtual BEHAVIOR_RESULT Run() override;
};

