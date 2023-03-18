#pragma once
#include "Common.h"

class GuiBase
{
public:
	GuiBase();
	virtual ~GuiBase();

public:
	void	InsertSeparator(); 

protected:
	ImVec2 m_vWindowSize;
};

