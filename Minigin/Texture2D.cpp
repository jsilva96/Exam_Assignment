#include "MiniginPCH.h"
#include "Texture2D.h"
#include "SomeStructs.h"
#include <SDL.h>

dae::Texture2D::Texture2D(SDL_Texture* tex, float width, float height, unsigned int id)
	:mTexture{ tex },
	m_Heigth{ height },
	m_Width{ width },
	m_ID{ id }
{
}
dae::Texture2D::Texture2D(SDL_Texture* tex)
	: dae::Texture2D::Texture2D(tex, m_Width, m_Heigth, m_ID)
{
}
dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(mTexture);
}
SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return mTexture;
}
float dae::Texture2D::GetHeight() const
{
	return m_Heigth;
}
float dae::Texture2D::GetWidth() const
{
	return m_Width;
}
unsigned int dae::Texture2D::GetID() const
{
	return m_ID;
}