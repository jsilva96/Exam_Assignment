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

	void Reset() override;

	void SetTexture(const string& filename);
	void SetActive(bool b);
	bool IsActive() const;
	dae::Texture2D* GetTexture() const;

protected:
	dae::Texture2D* m_Texture;
	Rectf m_DrawRect;

	bool m_IsActive = true;
private:

	RenderComponent(const RenderComponent& obj) = delete;
	RenderComponent(const RenderComponent&& obj) = delete;

	RenderComponent& operator=(const RenderComponent& obj) = delete;
	RenderComponent& operator=(const RenderComponent&& obj) = delete;
};

