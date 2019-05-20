#include "MiniginPCH.h"
#include "TextureManager.h"
#include "Texture2D.h"
#include <SDL_image.h>
#include "Renderer.h"
#include <gl/GL.h>

TextureManager::~TextureManager()
{
	for(auto& p : m_Textures) DeleteCheck(p.second);
}
dae::Texture2D* TextureManager::GetTexture(const std::string& path)
{
	auto it = m_Textures.find(path);
	if (it == m_Textures.end()) return CreateNewTexture(path);

	return (*it).second;
}

dae::Texture2D* TextureManager::CreateNewTexture(const std::string& path)
{
	SDL_Texture *texture = IMG_LoadTexture(dae::Renderer::GetInstance().GetSDLRenderer(), path.c_str());
	SDL_Surface *data = IMG_Load(path.c_str());

	if (!texture)
	{
		std::stringstream ss; ss << "Failed to load texture: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}

	auto height = data->h;
	auto width = data->w;

	GLuint id;
	glGenTextures(1, &id);

	SDL_FreeSurface(data);

	auto tex = new dae::Texture2D(texture, float(width), float(height), id);

	m_Textures[path] = tex;

	return tex;
}
