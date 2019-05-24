#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Components.h"
#include "Time.h"
#include "PoolManager.h"
#include "SomeStructs.h"
#include "BaseObserver.h"


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
	DeleteCheck(m_Observers);

	m_Tags.clear();
}

void* GameObject::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<GameObject>();
}
void GameObject::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<GameObject>(ptrDelete);
}

void GameObject::Initialize()
{
	if (m_IsInitialized) return;

	if (!m_pTransform)
	{
		m_pTransform = new TransformComponent();
		AddComponent(m_pTransform);
	}
	for (size_t i = 0; i < m_pChildren.size(); i++) if (m_pChildren[i]->IsUsable())m_pChildren[i]->Initialize();
	for (size_t i = 0; i < m_pComponents.size(); i++) m_pComponents[i]->Initialize();

	m_IsInitialized = true;
}
void GameObject::Update()
{
	for (GameObject* pObj : m_pChildren) if (pObj->IsUsable() && pObj->IsActive()) pObj->Update();
	for (BaseComponent* pC : m_pComponents) if (pC->IsUsable() && pC->IsActive()) pC->Update();
}
void GameObject::Render() const
{
	for (GameObject* pObj : m_pChildren) if (pObj->IsUsable() && pObj->IsActive()) pObj->Render();
	for (BaseComponent* pC : m_pComponents) if (pC->IsUsable() && pC->IsActive()) pC->Render();
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
	if (AddCheck(m_pComponents, pComp))
	{
		pComp->SetGameObject(this);
		if (m_IsInitialized) pComp->Initialize();
	}
}

void GameObject::AddTag(unsigned tag)
{
	if(!CompareTag(tag)) m_Tags.push_back(tag);
}
bool GameObject::CompareTag(unsigned tag)
{
	return std::find(m_Tags.begin(), m_Tags.end(), tag) != m_Tags.end();
}
void GameObject::AddObserver(BaseObserver* pObserver)
{
	AddCheck(m_Observers, pObserver);
}
void GameObject::OnNotify(unsigned event)
{
	for(auto& pObs : m_Observers) pObs->onNotify(this, event);
}
void GameObject::SetPosition(float x, float y)
{
	if(m_pTransform)m_pTransform->SetPosition(Point2f(x, y));
}

void GameObject::SetActive(bool isActive)
{
	if (isActive == IsActive()) return;

	BaseObject::SetActive(isActive);

	for (GameObject* pObj : m_pChildren) if (pObj->IsUsable()) pObj->SetActive(isActive);
	for (BaseComponent* pC : m_pComponents) if (pC->IsUsable()) pC->SetActive(isActive);
}

TransformComponent* GameObject::GetTransform() const
{
	return m_pTransform;
}
void GameObject::AddChild(GameObject * pObj)
{
	if(AddCheck(m_pChildren, pObj) && m_IsInitialized) pObj->Initialize();
}