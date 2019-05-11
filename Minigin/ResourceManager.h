#pragma once
#include "Singleton.h"

#include <fstream>
#include <string>
#include <iostream>

class TextureManager;
class MusicManager;
namespace dae
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
		std::string mDataPath;
	public:
		ResourceManager() = default;
		~ResourceManager();

		void Init(std::string&& data);

		Texture2D* LoadTexture(const std::string& file);
		std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size);
		int LoadSoundEffect(const std::string& file);
		int LoadSoundStream(const std::string& file);
		std::ifstream LoadTxtFile(const std::string& fileString);
		std::vector<Point2f> LoadSVGFile(const std::string& fileString);

	private:
		TextureManager* m_pTexManager;
		MusicManager* m_pManager;
	};

}
