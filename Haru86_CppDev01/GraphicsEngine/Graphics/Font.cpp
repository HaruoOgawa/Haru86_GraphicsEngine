#include "Font.h"
#include "./Texture.h"

Font::Font() {

}

Font::~Font() {
	UnLoad();
}

bool Font::Load(std::string fontPass) {
	if (TTF_Init() != 0) {
		SDL_Log("Cannot Initialize TTF");
		return false;
	}
	
	std::vector<int> fontSizes = {
		8, 9,
		10, 11, 12, 14, 16, 18,
		20, 22, 24, 26, 28,
		30, 32, 34, 36, 38,
		40, 42, 44, 46, 48,
		52, 56,
		60, 64, 68,
		72
	};

	for (auto size : fontSizes) {
		TTF_Font* font = TTF_OpenFont(fontPass.c_str(), size);
		if (font == nullptr) {
			SDL_Log("Can not Load Font Data: %s",TTF_GetError());
			return false;
		}
		fontData.emplace(size, font);
	}

	//printf("fontData.size: %d \n",fontData.size());

	return true;
}

void Font::UnLoad() {
	for (auto font : fontData) {
		TTF_CloseFont(font.second);
	}
	fontData.clear();
	TTF_Quit();
}

std::shared_ptr<Texture> Font::GetFontTexture(const std::string fontText, const glm::vec3 color, int fontSize) {
	std::shared_ptr<Texture> texture = nullptr;

	

	SDL_Color sdlColor;
	sdlColor.r = static_cast<Uint8>(color.x * 0);
	sdlColor.g = static_cast<Uint8>(color.y * 0);
	sdlColor.b = static_cast<Uint8>(color.z * 0);
	sdlColor.a = 255;

	printf("sdlColor r:%d , g:%d , b:%d a:%d \n",static_cast<int>(sdlColor.r), static_cast<int>(sdlColor.g), static_cast<int>(sdlColor.b), static_cast<int>(sdlColor.a));
	
	auto iter = fontData.find(fontSize);
	if (iter!=fontData.end()) {
		TTF_Font* font = iter->second;

		printf("fontText.c_str(): %s \n", fontText.c_str());

		SDL_Surface* surf = TTF_RenderUTF8_Blended(font, fontText.c_str(), sdlColor);
		
		if (surf != nullptr) {
			texture = std::make_shared<Texture>();
			texture->CreateTrueTypeFontTexture(surf);
			SDL_FreeSurface(surf);
			printf("Surf is NOT nullptr!!!!! \n");
		}
		else {
			printf("Surf is nullptr... \n");
		}
	}
	else {
		SDL_Log("Cannnot Get FontText");
	}

	return texture;
}