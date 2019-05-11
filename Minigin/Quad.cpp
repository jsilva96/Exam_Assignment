#include "MiniginPCH.h"
#include "Quad.h"
#include "Renderer.h"

Quad::Quad()
	:BaseShape(4)
{
}
void Quad::Initialize()
{
	m_Rect.leftBottom = { 0.0f, 0.0f };
	m_Rect.width = m_Length;
	m_Rect.height = m_Length;
}
void Quad::Render() const
{
	dae::Renderer::GetInstance().RenderRect(m_Rect, m_Color);
}
void Quad::Update()
{
}
void Quad::Reset()
{
	BaseShape::Reset();
}
