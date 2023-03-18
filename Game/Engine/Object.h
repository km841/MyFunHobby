#pragma once

enum class OBJECT_TYPE : uint8
{
	NONE,
	ANIMATION,
	GAMEOBJECT,
	COMPONENT,
	MATERIAL,
	MESH,
	SHADER,
	TEXTURE,
	PROPERTIES,

	END
};


enum
{
	OBJECT_TYPE_COUNT = static_cast<uint8>(OBJECT_TYPE::END),
};


class Object
{
public:
	Object(OBJECT_TYPE eType);
	virtual ~Object();

	void SetName(const wstring& szName) { m_szName = szName; }
	const wstring& GetName() { return m_szName; }

	OBJECT_TYPE GetType() { return m_eType; }

protected:
	friend class Resources;
	virtual void Load(const wstring& szPath) { }
	virtual void Save(const wstring& szPath) { }

protected:
	OBJECT_TYPE		m_eType;
	wstring			m_szName;
};

