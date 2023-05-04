#pragma once
class Skul;
class Cemetery
{
	DECLARE_SINGLE(Cemetery);
public:
	void Init();
	shared_ptr<Skul> Get(SKUL_KIND eSkulType);

	void Destroy();

private:
	void CreateSkul();

private:
	std::map<SKUL_KIND, shared_ptr<Skul>> m_mSkulMap;
};

