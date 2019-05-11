#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <windows.h>
#include <gl\GL.h>

#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"
#include "SVGParser.h"

#include "TextureManager.h"
#include "MusicManager.h"
#include <unordered_map>

dae::ResourceManager::~ResourceManager()
{
}

void dae::ResourceManager::Init(std::string&& dataPath)
{
	mDataPath = std::move(dataPath);

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		std::stringstream ss; ss << "Failed to load support for png: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}

	/*if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) {
		std::stringstream ss; ss << "Failed to load support for jpg: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}*/

	if (TTF_Init() != 0) {
		std::stringstream ss; ss << "Failed to load support for fonts: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}

	m_pTexManager = &TextureManager::GetInstance();
	m_pManager = &MusicManager::GetInstance();
}

dae::Texture2D* dae::ResourceManager::LoadTexture(const std::string& file)
{
	return	m_pTexManager->GetInstance().GetTexture(mDataPath + file);
}

std::shared_ptr<dae::Font> dae::ResourceManager::LoadFont(const std::string& file, unsigned int size)
{
	std::string fullPath = (mDataPath + file).c_str();
	return std::make_shared<Font>(fullPath, size);
}
int dae::ResourceManager::LoadSoundEffect(const std::string& file)
{
	return m_pManager->LoadEffect(mDataPath + file);
}
int dae::ResourceManager::LoadSoundStream(const std::string& file)
{
	return m_pManager->LoadStream(mDataPath + file);
}

std::ifstream dae::ResourceManager::LoadTxtFile(const std::string & fileString)
{
	std::string fullPath = (mDataPath + fileString).c_str();
	std::ifstream file{ fullPath };

	if (!file)
	{
		std::stringstream ss; ss << "Failed to load txt.file: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}

	return file;
}

std::vector<Point2f> dae::ResourceManager::LoadSVGFile(const std::string & fileString)
{
	std::vector<Point2f> obj;

	SVGParser::GetVerticesFromSvgFile(mDataPath + fileString, obj);

	return obj;
}
