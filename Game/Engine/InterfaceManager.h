#pragma once
class Interface;
class UI;
class HUD;
class InterfaceManager
{
	DECLARE_SINGLE(InterfaceManager);
public:
	void Init();

	shared_ptr<Interface> Get(INTERFACE_TYPE eInterfaceType);
	shared_ptr<UI> Get(UI_TYPE eUIType);
	shared_ptr<HUD> Get(HUD_TYPE eHUDType);

private:
	void CreateUI();
	void CreateHUD();

private:
	std::map<INTERFACE_TYPE, shared_ptr<Interface>> m_mInterfaceMap;
};

