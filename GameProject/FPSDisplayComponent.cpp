#include "pch.h"
#include "FPSDisplayComponent.h"

#include "PoolManager.h"
#include "Time.h"

#include "TextComponent.h"

void* FPSDisplayComponent::operator new(size_t nBytes)
{
	return PoolManager::GetInstance().RetrieveObject<FPSDisplayComponent>();
}
void FPSDisplayComponent::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject(static_cast<BaseObject*>(ptrDelete));
}
void FPSDisplayComponent::Initialize()
{
}
void FPSDisplayComponent::Update()
{
	if (m_pText)
	{
		m_pText->SetText("Test");
	}
}
void FPSDisplayComponent::Render() const
{
}
void FPSDisplayComponent::SetTextComponent(TextComponent* pComp)
{
	m_pText = pComp;
}
