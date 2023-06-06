#include "pch.h"
#include "SpineTextureLoader.h"
#include "Resources.h"
#include "Texture.h"

SpineTextureLoader::SpineTextureLoader()
{
}

SpineTextureLoader::~SpineTextureLoader()
{
}

void SpineTextureLoader::load(spine::AtlasPage& page, const spine::String& path)
{
	wstring szPath = s2ws(path.buffer());
	shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(szPath, szPath);
	Vec3 vTexSize = pTexture->GetTexSize();

	page.texture = &pTexture;
	page.texturePath = path;
	page.width = static_cast<int32>(vTexSize.x);
	page.height = static_cast<int32>(vTexSize.y);
}

void SpineTextureLoader::unload(void* texture)
{

}
