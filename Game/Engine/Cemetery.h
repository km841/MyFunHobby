#pragma once
class Skul;
class Cemetery
{
	DECLARE_SINGLE(Cemetery);
public:
	void Init();
	shared_ptr<Skul> Get(SKUL_TYPE eSkulType);

private:
	void CreateSkul();

private:
	std::map<SKUL_TYPE, shared_ptr<Skul>> m_mSkulMap;
};

