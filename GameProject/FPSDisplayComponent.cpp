#include "pch.h"
#include "FPSDisplayComponent.h"

#include "PoolManager.h"
#include "Time.h"

#include "TextComponent.h"

void* FPSDisplayComponent::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<FPSDisplayComponent>();
}
void FPSDisplayComponent::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<FPSDisplayComponent>(ptrDelete);
}
void FPSDisplayComponent::Initialize()
{
	m_pText->SetText("Loading...");
}
void FPSDisplayComponent::Update()
{
	if (m_pText)
	{
		m_pText->SetText(to_string(Time::GetInstance().GetFPS()));
	}
}
void FPSDisplayComponent::Render() const
{
}
void FPSDisplayComponent::SetTextComponent(TextComponent* pComp)
{
	m_pText = pComp;
}
