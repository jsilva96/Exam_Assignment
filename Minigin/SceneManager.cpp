#include "MiniginPCH.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "PoolManager.h"

void SceneManager::AddScene(GameScene * pScene)
{
	if (AddCheck(m_pScenes, pScene) && pScene->IsUsable())
	{
		if (m_pScenes.size() == 1) SetScene(pScene->GetID());
		pScene->RootInitialize();
	}
}
void SceneManager::SetScene(unsigned sceneID)
{
	if (m_pCurrentScene)
	{
		if (m_pCurrentScene->GetID() == sceneID) return;
	}

	auto it = std::find_if(m_pScenes.begin(), m_pScenes.end(), [sceneID](GameScene* pScene)
	{
		return pScene->GetID() == sceneID;
 	});

	if (it == m_pScenes.end()) throw std::runtime_error("SceneManager::SetScene->Invalid ID " + std::to_string(sceneID) + " not found/n");

	m_pCurrentScene = (*it);
	m_pCurrentScene->RootInitialize();
}
SceneManager::~SceneManager()
{
}
void SceneManager::Update()
{
	if (m_pCurrentScene) m_pCurrentScene->RootUpdate();
}
void SceneManager::Render()
{
	if (m_pCurrentScene) m_pCurrentScene->RootUpdate();
}
void SceneManager::Destroy()
{
	DeleteCheck(m_pScenes);
	m_pScenes.clear();
}
