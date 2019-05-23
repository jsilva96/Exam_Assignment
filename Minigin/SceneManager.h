#pragma once
#include "Singleton.h"

class GameScene;
class SceneManager final : public dae::Singleton<SceneManager>
{
public:
	virtual ~SceneManager();

	void AddScene(GameScene* pScene);
	void SetScene(unsigned int sceneID);
	
	void Update();
	void Render();
	void Destroy();

private:
	std::vector<GameScene*> m_pScenes;

	GameScene* m_pCurrentScene = nullptr;
};
