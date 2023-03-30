#pragma once

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

