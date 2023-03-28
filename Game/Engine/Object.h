#pragma once

enum class PLAYER_STATE : uint8
{
	IDLE,
	WALK,
	JUMP_RISE,
	JUMP_FALL,


	END,
};

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

	FORCEINLINE void SetName(const wstring& szName) { m_szName = szName; }
	FORCEINLINE const wstring& GetName() const { return m_szName; }

	FORCEINLINE OBJECT_TYPE GetType() const { return m_eType; }

protected:
	friend class Resources;
	virtual void Load(const wstring& szPath) { }
	virtual void Save(const wstring& szPath) { }

protected:
	OBJECT_TYPE		m_eType;
	wstring			m_szName;
};

