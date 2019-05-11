#pragma once
#include <SDL_ttf.h>

namespace dae
{
	class Font
	{
	public:
		TTF_Font* GetFont() const;
		explicit Font(const std::string& fullPath, unsigned int size);
		~Font();

	private:
		TTF_Font* mFont;
		unsigned int mSize;

		Font(const Font& obj) = delete;
		Font(const Font&& obj) = delete;
		Font& operator=(const Font& obj) = delete;
		Font& operator=(const Font&& obj) = delete;
	};

}
