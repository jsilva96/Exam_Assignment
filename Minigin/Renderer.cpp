#include "MiniginPCH.h"
#include "Renderer.h"

#include <gl/GLU.h>

#include "SceneManager.h"
#include "Texture2D.h"
#include "SomeStructs.h"
#include "SDL_rect.h"

void dae::Renderer::Init(SDL_Window * window, float heightOffset)
{
	mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	m_Screen = SDL_GetWindowSurface(window);


	m_HeightOffset = heightOffset;
	if (!mRenderer) 
	{
		std::stringstream ss; ss << "SDL_CreateRenderer Error: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}
}

void dae::Renderer::Render()
{
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_RenderClear(mRenderer);

	SceneManager::GetInstance().Render();

	SDL_RenderPresent(mRenderer);
}

void dae::Renderer::Destroy()
{
	if (mRenderer != nullptr)
	{
		SDL_DestroyRenderer(mRenderer);
		mRenderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const TransformInfo& info, const Rectf& dstRect) const
{
	RenderTexture(texture, dstRect.leftBottom.x, dstRect.leftBottom.y, info);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const TransformInfo& info) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);

	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);

	dst.y = (int)m_HeightOffset - dst.y - dst.h;

	SDL_RenderCopyEx(mRenderer, texture.GetSDLTexture(), nullptr, &dst, info.rotation, nullptr, SDL_FLIP_NONE);
}
void dae::Renderer::RenderShape(const std::vector<Point2f>& points, const Color4f& color)
{
	UNREFERENCED_PARAMETER(color);
	std::vector<Sint16> xPos;
	std::vector<Sint16> yPos;

	for (const Point2f& p : points)
	{
		xPos.push_back(Sint16(p.x));
		yPos.push_back(Sint16(m_HeightOffset - p.y));
	}

//	polygonRGBA(m_Screen, xPos.data(), yPos.data(), int(points.size()), Uint8(color.r), Uint8(color.g), Uint8(color.b), Uint8(color.a));
}
void dae::Renderer::RenderRect(const Rectf & rect, const Color4f & color)
{
	UNREFERENCED_PARAMETER(color);

	SDL_SetRenderDrawColor(mRenderer, Uint8(color.r * 255), Uint8(color.g * 255), Uint8(color.b * 255), Uint8(color.a * 255));

	SDL_Rect r = GetSDLRect(rect);

	r.y += int(m_HeightOffset) - r.h;
	SDL_RenderFillRect(mRenderer, &r);
}
Rectf dae::Renderer::GetWindowDims() const
{
	return Rectf({ 0.0f, 0.0f },float(m_Screen->w), float(m_Screen->h));
}
void dae::Renderer::RenderTexture(const Texture2D& texture, const TransformInfo& info, const Rectf& dstRect, const Rectf& srcRect) const
{
	Rectf empty{};

	SDL_Rect src;
	src.x = int(srcRect.leftBottom.x);
	src.y = int(srcRect.leftBottom.y);
	src.w = int(srcRect.width);
	src.h = int(srcRect.height);

	SDL_Rect dst{ ApplyDstTransform(dstRect, info) };

	dst.y = int(m_HeightOffset) - dst.y - dst.h;

	if (srcRect == empty) RenderTexture(texture, dstRect.leftBottom.x, dstRect.leftBottom.y, info);
	
	else
	{
		SDL_RenderCopyEx(mRenderer, texture.GetSDLTexture(), &src, &dst, info.rotation, nullptr, SDL_FLIP_NONE);
	}
	
}
SDL_Rect dae::Renderer::ApplyDstTransform(const Rectf& rect, const TransformInfo& info) const
{
	Point2f pivot;
	Rectf temp{ rect };

	if (info.isPivotMiddle) pivot = { rect.leftBottom.x + (rect.width / 2.0f), rect.leftBottom.y + (rect.height / 2.0f) };
	else pivot = info.Pivot;

	temp.leftBottom -= pivot;

	temp.leftBottom.x *= info.scale.x;
	temp.width *= info.scale.x;

	temp.leftBottom.y *= info.scale.y;
	temp.height *= info.scale.y;

	temp.leftBottom += pivot;

	return GetSDLRect(temp);
}
SDL_Rect dae::Renderer::GetSDLRect(const Rectf& rect) const
{
	SDL_Rect obj;
	obj.x = int(rect.leftBottom.x);
	obj.y = int(rect.leftBottom.y);
	obj.w = int(rect.width);
	obj.h = int(rect.height);

	return obj;
}
