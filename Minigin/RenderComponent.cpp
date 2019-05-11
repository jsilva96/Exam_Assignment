#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "Texture2D.h"

RenderComponent::RenderComponent()
	:m_Texture{ nullptr }
//	m_DrawRect{ nullptr }
{
}
RenderComponent::~RenderComponent()
{
//	delete m_DrawRect;
//	m_DrawRect = nullptr;
	DeleteCheck(m_Texture);
}

void* RenderComponent::operator new(size_t nBytes)
{
	UNREFERENCED_PARAMETER(nBytes);
	return PoolManager::GetInstance().RetrieveObject<RenderComponent>();
}
void RenderComponent::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject(static_cast<BaseObject*>(ptrDelete));
}
void RenderComponent::Initialize()
{
//	m_DrawRect = new Rectf();

	m_DrawRect.leftBottom = m_pGameObject->GetTransform()->GetPosition();
}
void RenderComponent::Update()
{
//	if (!m_IsActive) return;
	m_DrawRect.leftBottom = m_pGameObject->GetTransform()->GetPosition();
}
void RenderComponent::Render() const
{
	if (m_Texture && m_IsActive)
	{
		dae::Renderer::GetInstance().RenderTexture(*m_Texture, m_pGameObject->GetTransform()->GetTransformInfo(), m_DrawRect);
	}
}
void RenderComponent::Reset()
{
	BaseComponent::Reset();

	m_IsActive = true;

//	delete m_DrawRect;
//	m_DrawRect = nullptr;
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
dae::Texture2D* RenderComponent::GetTexture() const
{
	return &(*m_Texture);
}
