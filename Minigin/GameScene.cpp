#include "MiniginPCH.h"
#include "GameScene.h"
#include "GameObject.h"
#include "PoolManager.h"

using namespace std;
GameScene::GameScene(const std::string& name)
	:m_Name{ name },
	m_IsPaused{ false }
{
}
GameScene::GameScene()
	: GameScene("Scene")
{
}
GameScene::~GameScene()
{
	DeleteCheck(m_pObjects);
	m_pObjects.clear();
}
void GameScene::RootInitialize()
{
	Initialize();

	for(size_t i = 0 ; i < m_pObjects.size(); i++)
	{
		m_pObjects[i]->SetScene(this);
		m_pObjects[i]->RootInitialize();
	}
}
void GameScene::RootUpdate()
{
	if (m_IsPaused) return;
	Update();
	
	for (GameObject* pOb : m_pObjects) if (pOb->IsUsable()) pOb->RootUpdate();
}
void GameScene::RootRender() const
{
	Render();

	for (GameObject* pOb : m_pObjects)if (pOb->IsUsable()) pOb->RootRender();
}
void GameScene::Add(GameObject* pObj)
{
	AddCheck(m_pObjects, pObj);
}
void GameScene::SetSceneName(const std::string & name)
{
	m_Name = name;
}
void GameScene::Pause()
{
	m_IsPaused = !m_IsPaused;
}
bool GameScene::IsPaused() const
{
	return m_IsPaused;
}
