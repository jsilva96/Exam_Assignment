#pragma once
#include "Singleton.h"
//#include "SomeStructs.h"
//#include "SDL_rect.h"

struct Color4f;
struct Point2f;
struct TransformInfo;
struct Rectf;

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Rect;

namespace dae
{
	class Texture2D;
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window, float heightOffset);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D& texture, const TransformInfo& info, const Rectf& dstRect, bool isFlippedH = false, bool isFlippedV = false) const;
		void RenderTexture(const Texture2D& texture, const TransformInfo& info, const Rectf& dstRect, const Rectf& srcRect, bool isFlippedH = false, bool isFlippedV = false) const;
		void RenderTexture(const Texture2D& texture, const float x, const float y, const TransformInfo& info, bool isFlippedH = false, bool isFlippedV = false) const;
		void RenderShape(const std::vector<Point2f>& points, const Color4f& color);
		void RenderRect(const Rectf& rect, const Color4f& color);

		SDL_Renderer* GetSDLRenderer() const { return mRenderer; }
		Rectf GetWindowDims() const;

	private:
		float m_HeightOffset;
		SDL_Renderer* mRenderer = nullptr;
		SDL_Surface* m_Screen = nullptr;

		SDL_Rect ApplyDstTransform(const Rectf& dstRect, const TransformInfo& info) const;
		SDL_Rect GetSDLRect(const Rectf& rect) const;
	};
}

