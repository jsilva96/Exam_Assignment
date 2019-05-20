#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "Texture2D.h"

RenderComponent::RenderComponent()
	:m_Texture{ nullptr }
{
}
RenderComponent::~RenderComponent()
{
	m_IsActive = true;
//	DeleteCheck(m_Texture);
}

void* RenderComponent::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<RenderComponent>();
}
void RenderComponent::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<RenderComponent>(static_cast<RenderComponent*>(ptrDelete));
}
void RenderComponent::Initialize()
{
//	m_DrawRect = new Rectf();

	m_DrawRect.leftBottom = GetGameObject()->GetTransform()->GetPosition();
}
void RenderComponent::Update()
{
//	if (!m_IsActive) return;
	m_DrawRect.leftBottom = GetGameObject()->GetTransform()->GetPosition();
}
void RenderComponent::Render() const
{
	/*Rectf tempRect = m_DrawRect;
	tempRect.width *= GetGameObject()->GetTransform()->GetScale().x;
	tempRect.height *= GetGameObject()->GetTransform()->GetScale().y;*/

	if (m_Texture && m_IsActive)
	{
		dae::Renderer::GetInstance().RenderTexture(*m_Texture, GetGameObject()->GetTransform()->GetTransformInfo(), m_DrawRect);
	}
}
void RenderComponent::SetTexture(const string& filepath)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(filepath);

	m_DrawRect.width = m_Texture->GetWidth();
	m_DrawRect.height = m_Texture->GetHeight();
}
void RenderComponent::SetActive(bool b)
{
	m_IsActive = b;
}
bool RenderComponent::IsActive() const
{
	return m_IsActive;
}

float RenderComponent::GetTextureHeight() const
{
	if (!m_Texture) throw std::exception("RenderComponent::GetTextureHeight->Texture is nullptr\n");
	return m_Texture->GetHeight();
}
float RenderComponent::GetTextureWidth() const
{
	if (!m_Texture) throw std::exception("RenderComponent::GetTextureWidth->Texture is nullptr\n");
	return m_Texture->GetWidth();
}