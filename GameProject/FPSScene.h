#pragma once
#include "GameScene.h"

class GameObject;
class TextComponent;
class FPSScene : public GameScene
{
public:
	FPSScene();
	virtual ~FPSScene() = default;

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	void Initialize() override;
	void Update() override;
	void Render() const override
	{
		
	}
	void Reset() override
	{
		
	}

	FPSScene(const FPSScene& obj) = delete;
	FPSScene(FPSScene&& obj) noexcept = delete;

	FPSScene& operator=(const FPSScene& obj) = delete;
	FPSScene& operator=(FPSScene&& obj) noexcept = delete;

	GameObject* m_pBackground;
	GameObject* m_pDAEText;
	GameObject* m_pFPS;

	TextComponent* m_pFPSText;
};

