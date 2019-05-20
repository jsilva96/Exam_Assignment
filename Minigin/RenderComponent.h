#pragma once
#include "BaseComponent.h"
#include <string>
#include <memory>
#include "SomeStructs.h"
using namespace std;

struct Rectf;

namespace dae
{
	class Texture2D;
}
class RenderComponent : public BaseComponent
{
public:
	RenderComponent();
	~RenderComponent();

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	void Initialize() override;
	void Update() override;
	void Render()const override;

	virtual void SetTexture(const string& filename);
	void SetActive(bool b);
	bool IsActive() const;

	float GetTextureHeight() const;
	float GetTextureWidth() const;

	void SetFlipped(bool isFlippedV, bool isFlippedH);
protected:
	dae::Texture2D* m_Texture;
	Rectf m_DrawRect;

	bool m_IsActive = true;
	bool m_IsFlippedH = false;
	bool m_IsFlippedV = false;

private:

	RenderComponent(const RenderComponent&) = delete;
	RenderComponent(RenderComponent&&) noexcept = delete;

	RenderComponent& operator=(const RenderComponent&) = delete;
	RenderComponent& operator=(RenderComponent&&) noexcept = delete;
};

