#pragma once
#include "./Texture.h"
#include <unordered_map>
#include <SDL_ttf.h>
#include <SDL.h>
#include <string>
#include <glm/glm.hpp>

class Font
{
public:
	Font();
	~Font();
	bool Load(std::string fontPass);
	void UnLoad();
	Texture* GetFontTexture(const std::string fontText,const glm::vec3 color,int fontSize);
private:
	std::unordered_map<int, TTF_Font*> fontData;
};

