#include "GuiBase.h"

GuiBase::GuiBase()
{
}

GuiBase::~GuiBase()
{
}

void GuiBase::InsertSeparator()
{
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
}