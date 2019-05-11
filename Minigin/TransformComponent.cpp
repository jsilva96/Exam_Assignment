#include "MiniginPCH.h"
#include "TransformComponent.h"


TransformComponent::TransformComponent()
	:m_TransformInfo{}
{
}
TransformComponent::~TransformComponent()
{
}

void* TransformComponent::operator new(size_t nBytes)
{
	UNREFERENCED_PARAMETER(nBytes);
	return PoolManager::GetInstance().RetrieveObject<TransformComponent>();
}
void TransformComponent::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject(static_cast<BaseObject*>(ptrDelete));
}
void TransformComponent::Initialize()
{
}
void TransformComponent::Update()
{
}
void TransformComponent::Render() const
{
}
Point2f TransformComponent::GetPosition() const
{
	return m_TransformInfo.translation;
}
void TransformComponent::Reset()
{
	BaseComponent::Reset();
	m_TransformInfo.Reset();
}
void TransformComponent::SetPosition(const Point2f& pos)
{
	m_TransformInfo.translation = pos;
}

float TransformComponent::GetRotation() const
{
	return m_TransformInfo.rotation;
}
void TransformComponent::SetRotation(float rot)
{
	m_TransformInfo.rotation = rot;
}

Point2f TransformComponent::GetScale() const
{
	return m_TransformInfo.scale;
}
void TransformComponent::SetScale(const Point2f& scale)
{
	m_TransformInfo.scale = scale;
}
void TransformComponent::SetScale(float scale)
{
	SetScale({ scale, scale });
}

void TransformComponent::SetPivotPoint(const Point2f& p)
{
	m_TransformInfo.Pivot = p;
	m_TransformInfo.isPivotMiddle = false;
}
Point2f TransformComponent::GetPivotPoint() const
{
	return m_TransformInfo.Pivot;
}
void TransformComponent::ResetPivot()
{
	m_TransformInfo.isPivotMiddle = true;
}

const TransformInfo TransformComponent::GetTransformInfo() const
{
	return m_TransformInfo;
}