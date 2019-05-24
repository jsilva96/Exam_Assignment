#include "MiniginPCH.h"
#include "GameScene.h"
#include "GameObject.h"
#include "PoolManager.h"

using namespace std;
GameScene::GameScene(unsigned int sceneID)
	:m_SceneID{ sceneID }
{
}
GameScene::~GameScene()
{
	DeleteCheck(m_pObjects);
	m_pObjects.clear();

	m_IsInitialized = false;
}
void GameScene::RootInitialize()
{
	if (m_IsInitialized) return;
	Initialize();

	for(size_t i = 0 ; i < m_pObjects.size(); i++)
	{
		m_pObjects[i]->SetScene(this);
		m_pObjects[i]->Initialize();
	}

	m_IsInitialized = true;
}
void GameScene::RootUpdate()
{
	Update();
	
	for (GameObject* pOb : m_pObjects) if (pOb->IsUsable() && pOb->IsActive()) pOb->Update();
}
void GameScene::RootRender() const
{
	Render();

	for (GameObject* pOb : m_pObjects)if (pOb->IsUsable() && pOb->IsActive()) pOb->Render();
}
void GameScene::Add(GameObject* pObj)
{
	if (AddCheck(m_pObjects, pObj) && !m_IsInitialized) pObj->Initialize();
}
void GameScene::SetActive(bool isActive)
{
	if (isActive == IsActive()) return;

	BaseObject::SetActive(isActive);

	for (GameObject* pObj : m_pObjects) if (pObj->IsUsable()) pObj->SetActive(isActive);
}
