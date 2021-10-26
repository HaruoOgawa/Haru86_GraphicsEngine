#pragma once
class Texture
{
public:
	Texture();
	~Texture();
	void CreateForRendering(int width, int height, unsigned int format);
	unsigned int GetTextureID() const { return mTextureID; }
	void SetActive(int index);
	void Unload();
private:
	unsigned int mTextureID;
	int mWidth;
	int mHeight;
};

