#include "MiniginPCH.h"
#include <memory>
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextComponent.h"
#include "TransformComponent.h"
#include "SomeStructs.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Font.h"

TextComponent::TextComponent()
	:m_pFont{ nullptr },
	m_Color{ 1,1,1,1 }
{
}
TextComponent::~TextComponent()
{
}

void* TextComponent::operator new(size_t nBytes)
{
	UNREFERENCED_PARAMETER(nBytes);
	return PoolManager::GetInstance().RetrieveObject<TextComponent>();
}
void TextComponent::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject(static_cast<BaseObject*>(ptrDelete));
}
void TextComponent::Initialize()
{
	RenderComponent::Initialize();
}
void TextComponent::Update()
{
	if (!m_Text.empty())
	{
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), ToSDLColor(m_Color));
		if (surf == nullptr) {
			std::stringstream ss; ss << "Render text failed: " << SDL_GetError();
			throw std::runtime_error(ss.str().c_str());
		}
		auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) {
			std::stringstream ss; ss << "Create text texture from surface failed: " << SDL_GetError();
			throw std::runtime_error(ss.str().c_str());
		}
		SDL_FreeSurface(surf);
		
		delete m_Texture;
		m_Texture = new dae::Texture2D(texture);
	}
	RenderComponent::Update();
}
void TextComponent::Render() const
{
	if (m_Texture)
	{
	//	Point2f p = m_pGameObject->GetTransform()->GetPosition();
	//	dae::Renderer::GetInstance().RenderTexture(*m_Texture, p.x, p.y);
		dae::Renderer::GetInstance().RenderTexture(*m_Texture, m_pGameObject->GetTransform()->GetTransformInfo(), m_DrawRect);
	}
}
void TextComponent::Reset()
{
	RenderComponent::Reset();

	m_Color = { 0, 0, 0, 1 };
	m_Text.clear();
}
void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
}
void TextComponent::SetFont(const std::string& path, unsigned int size)
{
	m_pFont = dae::ResourceManager::GetInstance().LoadFont(path, size);
}
void TextComponent::SetColor(const Color4f& color)
{
	m_Color = color;
}

SDL_Color TextComponent::ToSDLColor(const Color4f& c) const
{
	SDL_Color obj;

	obj.r = Uint8(c.r * 255);
	obj.g = Uint8(c.g * 255);
	obj.b = Uint8(c.b * 255);
	obj.a = Uint8(c.a * 255);

	return obj;
}
