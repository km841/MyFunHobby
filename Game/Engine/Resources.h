#pragma once

#include "GameObject.h"
#include "Texture.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "Animation.h"


class Resources
{
	DECLARE_SINGLE(Resources);

public:
	void Init();

	shared_ptr<Texture> CreateTexture(const wstring& szName, DXGI_FORMAT eFormat, uint32 eType, uint32 iWidth, uint32 iHeight);
	shared_ptr<Texture> CreateTextureFromResource(const wstring& szName, DXGI_FORMAT eFormat, uint32 eType, ComPtr<ID3D11Texture2D> iTexture);

	template<typename T>
	shared_ptr<T> Load(const wstring& szKey, const wstring& szPath);

	template<typename T>
	bool Add(const wstring& szKey, shared_ptr<T> pObject);

	template<typename T>
	shared_ptr<T> Get(const wstring& szKey);

	template<typename T>
	OBJECT_TYPE GetObjectType();

	shared_ptr<Mesh> LoadRectMesh();
	shared_ptr<Mesh> LoadCircleMesh();

	void CreateDefaultShader();
	void CreateDefaultMaterial();

private:
	using KeyObjMap = std::map<wstring, shared_ptr<Object>>;
	std::array<KeyObjMap, OBJECT_TYPE_COUNT> m_arrResources;


};

template<typename T>
inline shared_ptr<T> Resources::Load(const wstring& szKey, const wstring& szPath)
{
	OBJECT_TYPE eObjType = GetObjectType<T>();
	KeyObjMap& mObjMap = m_arrResources[static_cast<uint8>(eObjType)];

	auto findIt = mObjMap.find(szKey);
	if (mObjMap.end() != findIt)
		return static_pointer_cast<T>(findIt->second);

	shared_ptr<T> pObject = make_shared<T>();
	pObject->Load(szPath);
	mObjMap[szKey] = pObject;

	return pObject;
}

template<typename T>
inline bool Resources::Add(const wstring& szKey, shared_ptr<T> pObject)
{
	OBJECT_TYPE eObjType = GetObjectType<T>();
	KeyObjMap& mObjMap = m_arrResources[static_cast<uint8>(eObjType)];

	auto findIt = mObjMap.find(szKey);
	if (mObjMap.end() != findIt)
		return false;

	mObjMap[szKey] = pObject;
	return true;
}

template<typename T>
inline shared_ptr<T> Resources::Get(const wstring& szKey)
{
	OBJECT_TYPE eObjType = GetObjectType<T>();
	KeyObjMap& mObjMap = m_arrResources[static_cast<uint8>(eObjType)];

	auto findIt = mObjMap.find(szKey);
	if (mObjMap.end() != findIt)
		return static_pointer_cast<T>(findIt->second);

	return nullptr;
}

template<typename T>
inline OBJECT_TYPE Resources::GetObjectType()
{
	if (std::is_same_v<T, GameObject>)
		return OBJECT_TYPE::GAMEOBJECT;
	else if (std::is_same_v<T, Texture>)
		return OBJECT_TYPE::TEXTURE;
	else if (std::is_same_v<T, Shader>)
		return OBJECT_TYPE::SHADER;
	else if (std::is_same_v<T, Material>)
		return OBJECT_TYPE::MATERIAL;
	else if (std::is_same_v<T, Component>)
		return OBJECT_TYPE::COMPONENT;
	else if (std::is_same_v<T, Animation>)
		return OBJECT_TYPE::ANIMATION;
	else
		return OBJECT_TYPE::NONE;
}
