#pragma once
#include "BaseObject.h"
#include <vector>
#include <string>

class GameObject;
class GameScene : public BaseObject
{
public:
	explicit GameScene(unsigned int sceneID);
	virtual ~GameScene();

	void Add(GameObject* pObj);
	unsigned int GetID() const { return m_SceneID; };

	template<class T> T* GetGameObject()
	{
		const type_info& ti = typeid(T);
		for (GameObject* pObj : m_pObjects)
		{
			if (pObj && typeid(*pObj) == ti) return static_cast<T*>(pObj);
		}

		return nullptr;
	}

	void SetActive(bool isActive) override;

private:
	std::vector<GameObject*> m_pObjects;
	unsigned int m_SceneID;
	bool m_IsInitialized = false;

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

