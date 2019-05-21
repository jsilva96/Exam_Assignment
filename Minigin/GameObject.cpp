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

	m_Tags.clear();
}

void* GameObject::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<GameObject>();
}
void GameObject::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<GameObject>(static_cast<GameObject*>(ptrDelete));
}
void GameObject::RootInitialize()
{
	if (!m_pTransform)
	{
		m_pTransform = new TransformComponent();
		AddComponent(m_pTransform);
	}
	Initialize();

	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		if(m_pChildren[i]->IsUsable())m_pChildren[i]->RootInitialize();
	}
	for (size_t i = 0; i < m_pComponents.size(); i++)
	{
		m_pComponents[i]->Initialize();
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

void GameObject::AddTag(unsigned tag)
{
	if(!CompareTag(tag)) m_Tags.push_back(tag);
}
bool GameObject::CompareTag(unsigned tag)
{
	return std::find(m_Tags.begin(), m_Tags.end(), tag) != m_Tags.end();
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