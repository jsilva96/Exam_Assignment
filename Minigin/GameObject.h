#pragma once
#include <memory>
#include <vector>
#include "BaseObject.h"

class BaseComponent;
class TransformComponent;
class GameScene;

struct HitInfo;
class GameObject : public BaseObject
{
public:
	GameObject();
	virtual ~GameObject();

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	virtual void Initialize(){};
	virtual void Update(){};
	virtual void Render() const{};
	
	virtual void OnCollide(GameObject* pObj);
	virtual void OnLevelCollide(HitInfo info);

	void RootInitialize();
	void RootUpdate();
	void RootRender() const;

	void SetScene(GameScene* pScene);
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

protected:
	TransformComponent * m_pTransform;
	std::vector<BaseComponent*> m_pComponents;
	GameScene* m_pScene;
	std::vector<GameObject*> m_pChildren;

private:
	GameObject(const GameObject& other) = delete;
	GameObject(const GameObject&& other) = delete;

	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(const GameObject&& other) = delete;

};
