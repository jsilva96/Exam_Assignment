#pragma once
#include <BaseComponent.h>
#include "SomeStructs.h"

class TextComponent;
class SelectionComponent final: public BaseComponent
{
public:
	SelectionComponent() = default;
	virtual ~SelectionComponent() = default;

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	void Initialize() override;
	void Update() override;
	void Render() const override;

	void SetSelected(bool isSelected);
	bool IsSelected() const { return m_IsSelected; }

	SelectionComponent(const SelectionComponent&) = delete;
	SelectionComponent(SelectionComponent&&) noexcept = delete;

	SelectionComponent& operator=(const SelectionComponent&) = delete;
	SelectionComponent& operator=(SelectionComponent&&) noexcept = delete;
private:
	TextComponent* m_TextComp = nullptr;

	Color4f m_SelectColor, m_UnselectColor;
	bool m_IsSelected = false;

};

