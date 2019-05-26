#pragma once
#include <BaseComponent.h>

struct Vector2f;
class RenderComponent;
class ColliderComponent;
class TranslationComponent;
class HookComponent final : public BaseComponent
{
public:
	HookComponent() = default;
	virtual ~HookComponent();

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	void Initialize() override;
	void Update() override;
	void Render() const override;

	void UseHook(const Vector2f& v);

	bool IsLaunched() const;

	HookComponent(const HookComponent&) = delete;
	HookComponent(HookComponent&&) noexcept = delete;

	HookComponent& operator=(const HookComponent&) = delete;
	HookComponent& operator=(HookComponent&&) noexcept = delete;
private:
	GameObject* m_pHook = nullptr;

	RenderComponent* m_pRender = nullptr;
	ColliderComponent* m_pCollider = nullptr;
	TranslationComponent* m_pTrans = nullptr;
};