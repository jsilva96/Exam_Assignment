#pragma once
#include "BaseObject.h"
#include <vector>
#include <string>

class GameObject;
class GameScene : public BaseObject
{
public:
	explicit GameScene(const std::string& name);
	explicit GameScene();
	virtual ~GameScene();

	void Add(GameObject* pObj);
	void SetSceneName(const std::string& name);

	template<class T> T* GetGameObject()
	{
		const type_info& ti = typeid(T);
		for (GameObject* pObj : m_pObjects)
		{
			if (pObj && typeid(*pObj) == ti) return static_cast<T*>(pObj);
		}

		return nullptr;
	}

	void Pause();
	bool IsPaused() const;
private:
	std::vector<GameObject*> m_pObjects;
	std::string m_Name;
	bool m_IsPaused;

	friend class SceneManager;

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() const = 0;

	void RootInitialize();
	void RootUpdate();
	void RootRender() const;
	
	GameScene(const GameScene&) = delete;
	GameScene(GameScene&&) noexcept = delete;

	GameScene& operator=(const GameScene&) = delete;
	GameScene& operator=(GameScene&&) noexcept = delete;

};

