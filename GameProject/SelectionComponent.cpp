#include "pch.h"
#include "SelectionComponent.h"

#include "PoolManager.h"
#include "TextComponent.h"
void* SelectionComponent::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<SelectionComponent>();
}
void SelectionComponent::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<SelectionComponent>(ptrDelete);
}
void SelectionComponent::Initialize()
{
	m_TextComp = GetGameObject()->GetComponent<TextComponent>();

	if(!m_TextComp) throw std::runtime_error("SelectionComponent::Initialize->TextComponent not found\n");

	m_SelectColor = { 0.0f, 1.0f, 0.0f, 1.0f };
	m_UnselectColor = { 1.0f, 1.0f, 1.0f, 1.0f };

	m_TextComp->SetColor(m_IsSelected ? m_SelectColor : m_UnselectColor);
}
void SelectionComponent::Update()
{
}
void SelectionComponent::Render() const
{
}
void SelectionComponent::SetSelected(bool isSelected)
{
	if (m_IsSelected == isSelected) return;

	m_IsSelected = isSelected;

	if(m_TextComp)m_TextComp->SetColor(m_IsSelected ? m_SelectColor : m_UnselectColor);
}