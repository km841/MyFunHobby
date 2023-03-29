#pragma once
class UI;
class UIManager
{
	DECLARE_SINGLE(UIManager);
public:
	void Init();

	shared_ptr<UI> Get(UI_TYPE eUIType);


private:
	void CreateUI();
	

private:
	std::map<UI_TYPE, shared_ptr<UI>> m_mUIMap;
};

