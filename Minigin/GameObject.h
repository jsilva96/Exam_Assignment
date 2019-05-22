#pragma once
#include <memory>
#include <vector>
#include "BaseObject.h"

class BaseComponent;
class TransformComponent;
class GameScene;
class BaseObserver;

class GameObject final : public BaseObject
{
public:
	GameObject();
	virtual ~GameObject();

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	GameScene* GetScene() const;

	void SetPosition(float x, float y);

	template<class T> T* GetComponent()
	{
		const type_info& ti = typeid(T);
		for (BaseComponent* component : m_pComponents)
		{
			if (component && typeid(*component) == ti) return static_cast<T*>(component);
		}

		return nullptr;
	}

	TransformComponent* GetTransform() const;
	void AddChild(GameObject* pObj);

	void AddComponent(BaseComponent* pComp);
	void AddTag(unsigned int tag);
	bool CompareTag(unsigned int tag);

	void AddObserver(BaseObserver* pObserver);
	void OnNotify(unsigned int event);
private:

	friend class GameScene;
	void Initialize();
	void Update();
	void Render() const;

	void SetScene(GameScene* pScene);

	TransformComponent * m_pTransform;
	std::vector<BaseComponent*> m_pComponents;
	GameScene* m_pScene;
	std::vector<GameObject*> m_pChildren;

	std::vector<unsigned int> m_Tags;

	std::vector<BaseObserver*> m_Observers;

	GameObject(const GameObject&) = delete;
	GameObject(GameObject&&) noexcept = delete;

	GameObject& operator=(const GameObject&) = delete;
	GameObject& operator=(GameObject&&) noexcept = delete;

};
