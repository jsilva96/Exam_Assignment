#pragma once
#include "Singleton.h"
#include <map>

namespace dae
{
	class Texture2D;
}

class TextureManager : public dae::Singleton<TextureManager>
{
public:
	TextureManager() = default;
	~TextureManager();

	dae::Texture2D* GetTexture(const std::string& path);
private:
	dae::Texture2D* CreateNewTexture(const std::string& path);

	std::map<std::string, dae::Texture2D*> m_Textures;
};

