#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Components.h"
#include "Time.h"
#include "PoolManager.h"
#include "SomeStructs.h"


GameObject::GameObject()
	:m_pScene{ nullptr },
	m_pTransform{}
{
	m_pTransform = new TransformComponent();
	AddComponent(m_pTransform);
}
GameObject::~GameObject()
{
	DeleteCheck(m_pComponents);
	DeleteCheck(m_pChildren);
}

void* GameObject::operator new(size_t nBytes)
{
	UNREFERENCED_PARAMETER(nBytes);
	return PoolManager::GetInstance().RetrieveObject<GameObject>();
}
void GameObject::operator delete(void* ptrDelete)
{
	return PoolManager::GetInstance().ReturnObject(static_cast<BaseObject*>(ptrDelete));
}

void GameObject::RootInitialize()
{
	if (!m_pTransform)
	{
		m_pTransform = new TransformComponent();
		AddComponent(m_pTransform);
	}
	Initialize();

	for (GameObject* pObj : m_pChildren) if (pObj->IsUsable()) pObj->RootInitialize();
	for (BaseComponent* pC : m_pComponents)
	{
		if (pC->IsUsable())
		{
			pC->Initialize();
		}
	}
}
void GameObject::RootUpdate()
{
	Update();

	for (GameObject* pObj : m_pChildren) if (pObj->IsUsable()) pObj->RootUpdate();
	for (BaseComponent* pC : m_pComponents) if (pC->IsUsable()) pC->Update();
}
void GameObject::RootRender() const
{
	Render();
	
	for (GameObject* pObj : m_pChildren) if (pObj->IsUsable()) pObj->RootRender();
	for (BaseComponent* pC : m_pComponents) if (pC->IsUsable()) pC->Render();
}
void GameObject::Reset()
{
	DeleteCheck(m_pComponents);
	DeleteCheck(m_pChildren);
}

void GameObject::OnCollide(GameObject*)
{
}
void GameObject::OnLevelCollide(HitInfo)
{
}
void GameObject::SetScene(GameScene * pScene)
{
	m_pScene = pScene;
}
GameScene * GameObject::GetScene() const
{
	return m_pScene;
}
void GameObject::AddComponent(BaseComponent* pComp)
{
	if (AddCheck(m_pComponents, pComp)) pComp->SetGameObject(this);
}
void GameObject::SetPosition(float x, float y)
{
	if(m_pTransform)m_pTransform->SetPosition(Point2f(x, y));
}
TransformComponent* GameObject::GetTransform() const
{
	return m_pTransform;
}
void GameObject::AddChild(GameObject * pObj)
{
	AddCheck(m_pChildren, pObj);
}
//template <class T>
//T* GameObject::GetComponent()
//{
//	const type_info& ti = typeid(T);
//	for (BaseComponent* component : m_pComponents)
//	{
//		if (component && typeid(*component) == ti) return static_cast<T*>(component);
//	}
//
//	return nullptr;
//}