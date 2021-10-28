#pragma once
#include <string>
#include <SDL.h>

class Texture
{
public:
	Texture();
	~Texture();
	void CreateForRendering(int width, int height, unsigned int format);
	void CreateTrueTypeFontTexture(SDL_Surface* surf);
	unsigned int GetTextureID() const { return mTextureID; }
	void SetActive();
	void Unload();
private:
	unsigned int mTextureID;
	int mWidth;
	int mHeight;
};

