#pragma once
#include <BaseComponent.h>

class SpriteComponent;
struct SpriteDesc;

class SpriteDescSwitchComponent final: public BaseComponent
{
public:
	SpriteDescSwitchComponent() = default;
	virtual ~SpriteDescSwitchComponent() = default;

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	void Initialize() override;
	void Update() override;
	void Render() const override;

	void AddDesc(const SpriteDesc& desc);
	void SetDesc(int index);

	SpriteDescSwitchComponent(const SpriteDescSwitchComponent& obj) = delete;
	SpriteDescSwitchComponent(SpriteDescSwitchComponent&& obj) noexcept = delete;

	SpriteDescSwitchComponent& operator=(const SpriteDescSwitchComponent& obj) = delete;
	SpriteDescSwitchComponent& operator=(SpriteDescSwitchComponent&& obj) noexcept = delete;
private:
	std::vector<SpriteDesc> m_SpriteDesc;
	SpriteComponent* m_SpriteComponent = nullptr;
};

