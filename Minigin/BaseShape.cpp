#include "MiniginPCH.h"
#include "BaseShape.h"

#include "Components.h"
#include "Renderer.h"
BaseShape::BaseShape(unsigned int nrOfVerts)
	:m_NrOfVerts{ nrOfVerts },
	m_Color{},
	m_Length{}
{
}
BaseShape::~BaseShape()
{
	m_Verts.clear();
	m_Length = 1.0f;
}
void BaseShape::Initialize()
{
	Point2f p{ m_pTransform->GetPosition() };
	Point2f center = p;
	float angle{};

	p.x += m_Length;
	m_Verts.push_back(p);

	for (size_t i = 1; i < m_NrOfVerts; i++)
	{
		angle += (2 * float(M_PI)) / m_NrOfVerts;

		p.x = center.x + (m_Length * 0.5f) * cos(angle);
		p.y = center.y + (m_Length * 0.5f) * sin(angle);

		m_Verts.push_back(p);
	}
}
void BaseShape::Update()
{
}
void BaseShape::Render() const
{
	dae::Renderer::GetInstance().RenderShape(m_Verts, m_Color);
}
void BaseShape::SetLength(float length)
{
	m_Length = length;
}
void BaseShape::SetColor(const Color4f& c)
{
	m_Color = c;
}
void BaseShape::OnCollide(GameObject * pObj)
{
	UNREFERENCED_PARAMETER(pObj);
}

void BaseShape::OnLevelCollide(HitInfo info)
{
	UNREFERENCED_PARAMETER(info);
}
