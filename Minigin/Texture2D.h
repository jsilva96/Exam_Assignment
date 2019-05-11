#pragma once
//#include <gl/GL.h>
//#include <gl\GL.h>

struct SDL_Texture;
namespace dae
{
	class Texture2D
	{
	public:
		Texture2D(SDL_Texture* tex, float width, float height, unsigned int id);
		Texture2D(SDL_Texture* tex);

		~Texture2D();

		SDL_Texture* GetSDLTexture() const;
		float GetHeight() const;
		float GetWidth() const;
		unsigned int GetID() const;

	private:
		SDL_Texture* mTexture;
		float m_Width;
		float m_Heigth;
		unsigned int m_ID;
		
		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;
	};
}
