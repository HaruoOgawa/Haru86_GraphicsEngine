#pragma once
#include <memory>

class Texture;

class CBloom
{

public:
	CBloom();
	~CBloom();
	void Initialize();
	void Draw(const std::shared_ptr<Texture> SrcTexture, const unsigned int& DestBuffer);
private:
	void Release();
};

