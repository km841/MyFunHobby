#pragma once
class Texture;
class Engrave
{
public:
	Engrave(ENGRAVE eEngrave);
	~Engrave();

public:
	static shared_ptr<Texture> GetEngraveTexture(ENGRAVE eEngrave, ENGRAVE_STATE eEngraveState);

	const wstring& GetName() { return m_szName; }
	ENGRAVE GetEngrave() { return m_eEngrave; }

public:
	shared_ptr<Texture> GetActivationTexture();
	shared_ptr<Texture> GetDectivationTexture();
	shared_ptr<Texture> GetFullActivationTexture();

protected:
	ENGRAVE_STATE m_eEngraveState;
	ENGRAVE m_eEngrave;

	wstring m_szComment;
	wstring m_szName;

	uint8 m_iFullCount;
};

