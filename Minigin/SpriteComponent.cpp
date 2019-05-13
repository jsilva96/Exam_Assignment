#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "Time.h"
#include "TransformComponent.h"

SpriteComponent::SpriteComponent(const SpriteDesc& desc)
	:m_CurrFrame{},
	m_SrcRect{ desc.startPos, desc.width, desc.height },
	m_SpriteInfo{ desc },
	m_Timer{},
	m_StopTimer{ false },
    m_RunCount{}
{
	m_CountRuns = desc.nrOfRuns > 0;
}
SpriteComponent::SpriteComponent()
	:SpriteComponent(SpriteDesc{ {},0,1,0,0,0,SpriteParse::HORIZONTAL })
{
}
SpriteComponent::~SpriteComponent()
{
	m_CurrFrame = 0;
	m_CountRuns = false;
	m_Timer = 0.0f;
	m_StopTimer = false;
	m_IsActive = true;

	m_SpriteInfo.Reset();

}
void* SpriteComponent::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<SpriteComponent>();
}
void SpriteComponent::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject(static_cast<BaseObject*>(ptrDelete));
}
void SpriteComponent::Initialize()
{
	RenderComponent::Initialize();

	m_SrcRect.leftBottom = m_SpriteInfo.startPos;
	m_SrcRect.height = m_SpriteInfo.height;
	m_SrcRect.width = m_SpriteInfo.width;
}
void SpriteComponent::Update()
{
	RenderComponent::Update();

	if (m_StopTimer || !m_IsActive) return;
	m_Timer += Time::GetInstance().GetElapsedSecs();

	switch (m_SpriteInfo.parseLogic)
	{
	case SpriteParse::HORIZONTAL:
		UpdateHorizontal();
		break;

	case SpriteParse::VERTICAL:
		UpdateVertical();
		break;
	case SpriteParse::CUSTOM:
		UpdateCustom();
		break;
	}
}
void SpriteComponent::UpdateHorizontal()
{
	if (m_Timer >= m_SpriteInfo.frameTime)
	{
		++m_CurrFrame;
		if (m_CurrFrame == m_SpriteInfo.frames)
		{
			if (m_CountRuns)
			{
				++m_RunCount;
				if (m_SpriteInfo.nrOfRuns <= int(m_RunCount))
				{
					m_IsActive = false;
					return;
				}
			}
			m_SrcRect.leftBottom.x = m_SpriteInfo.startPos.x;
			m_CurrFrame = 0;
		}
		else m_SrcRect.leftBottom.x += m_SpriteInfo.width;

		m_Timer -= m_SpriteInfo.frameTime;
	}
}
void SpriteComponent::UpdateVertical()
{
	if (m_Timer >= m_SpriteInfo.frameTime)
	{
		++m_CurrFrame;
		if (m_CurrFrame == m_SpriteInfo.frames)
		{
			if (m_CountRuns)
			{
				++m_RunCount;
				if (m_SpriteInfo.nrOfRuns <= int(m_RunCount))
				{
					m_IsActive = false;
					return;
				}
			}
			m_SrcRect.leftBottom.y = m_SpriteInfo.startPos.y;
			m_CurrFrame = 0;
		}
		else m_SrcRect.leftBottom.y += m_SpriteInfo.height;

		m_Timer -= m_SpriteInfo.frameTime;
	}
}
void SpriteComponent::Render() const
{
	if (m_Texture && m_IsActive)
	{
		dae::Renderer::GetInstance().RenderTexture(*m_Texture, GetGameObject()->GetTransform()->GetTransformInfo(), m_DrawRect, m_SrcRect);
	}
}
void SpriteComponent::SetTexture(const string& filename)
{
	RenderComponent::SetTexture(filename);

	m_DrawRect.height = m_SrcRect.height;
	m_DrawRect.width = m_SrcRect.width;
}
void SpriteComponent::StopTimer(bool b)
{
	m_StopTimer = b;
}
void SpriteComponent::SetDesc(const SpriteDesc & desc)
{
	if (desc == m_SpriteInfo) return;

	m_SpriteInfo = desc;
	
	m_SrcRect.leftBottom = m_SpriteInfo.startPos;
	m_SrcRect.height = m_SpriteInfo.height;
	m_SrcRect.width = m_SpriteInfo.width;

	m_DrawRect.height = m_SrcRect.height;
	m_DrawRect.width = m_SrcRect.width;

	m_CurrFrame = 0;

    m_CountRuns = m_SpriteInfo.nrOfRuns > 0;
	m_RunCount = 0;

	m_Timer = 0.0f;
}
