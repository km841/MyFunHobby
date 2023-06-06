#pragma once

class SpineTextureLoader
	: public spine::TextureLoader
{
public:
	SpineTextureLoader();
	virtual ~SpineTextureLoader();

public:
	virtual void load(spine::AtlasPage& page, const spine::String& path);
	virtual void unload(void* texture);
};

