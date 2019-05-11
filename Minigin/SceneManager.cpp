#include "MiniginPCH.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "PoolManager.h"

void SceneManager::AddScene(GameScene * pScene)
{
	if (AddCheck(m_pScenes, pScene) && pScene->IsUsable())pScene->RootInitialize();
}
SceneManager::~SceneManager()
{
}
void SceneManager::Update()
{
	for(auto scene : m_pScenes)
	{
		if(scene->IsUsable())scene->RootUpdate();
	}
}
void SceneManager::Render()
{
	for (auto scene : m_pScenes)
	{
		if (scene->IsUsable())scene->RootRender();
	}
}
void SceneManager::Destroy()
{
	for (GameScene* pScene : m_pScenes) delete pScene;

	m_pScenes.clear();
}
bool SceneManager::IsGameOver() const
{
	return m_IsGameOver;
}
void SceneManager::EndGame()
{
	m_IsGameOver = true;
}
