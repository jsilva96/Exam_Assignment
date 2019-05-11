#pragma once
#include "RenderComponent.h"

struct Color4f;
struct SDL_Color;
namespace dae
{
	class Font;
};
class TextComponent final : public RenderComponent
{
public:
	TextComponent();
	virtual ~TextComponent();

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	void Initialize() override;
	void Update() override;
	void Render() const override;

	void Reset() override;

	void SetText(const std::string& text);
	void SetFont(const std::string& path, unsigned int size);
	void SetColor(const Color4f& color);

private:
	std::string m_Text;
	std::shared_ptr<dae::Font> m_pFont;
	Color4f m_Color;

	SDL_Color ToSDLColor(const Color4f& c) const;

	TextComponent(const TextComponent& obj) = delete;
	TextComponent(const TextComponent&& obj) = delete;

	TextComponent& operator=(const TextComponent& obj) = delete;
	TextComponent& operator=(const TextComponent&& obj) = delete;
};

