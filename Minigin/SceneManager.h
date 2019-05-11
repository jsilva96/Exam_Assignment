#pragma once
#include "Singleton.h"

class GameScene;
class SceneManager final : public dae::Singleton<SceneManager>
{
public:
	virtual ~SceneManager();

	void AddScene(GameScene* pScene);
	void Update();
	void Render();
	void Destroy();
	bool IsGameOver() const;

	void EndGame();

private:
	std::vector<GameScene*> m_pScenes;
	bool m_IsGameOver = false;
};
