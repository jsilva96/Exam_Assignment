#pragma once
#include <BaseComponent.h>

class TextComponent;
class FPSDisplayComponent final : public BaseComponent
{
public:
	FPSDisplayComponent() = default;
	virtual ~FPSDisplayComponent() = default;

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	void Initialize() override;
	void Update() override;
	void Render() const override;

	void SetTextComponent(TextComponent* pComp);

	FPSDisplayComponent(const FPSDisplayComponent&) = delete;
	FPSDisplayComponent(FPSDisplayComponent&&) noexcept = delete;

	FPSDisplayComponent& operator=(const FPSDisplayComponent&) = delete;
	FPSDisplayComponent& operator=(FPSDisplayComponent&&) noexcept = delete;

private:
	TextComponent* m_pText = nullptr;
};

