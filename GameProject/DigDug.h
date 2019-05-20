#pragma once
#include <GameScene.h>
#include "SomeStructs.h"

class TimerComponent;
enum class PlayerState
{
	MOVING = 0,
	DIGING,
	HOOK,
	HOOKED,
	CRUSHED,
	DEAD
};

enum class FygarState
{
	MOVING = 0,
	PHASING,
	CRUSHED,
	HOOKED_1,
	HOOKED_2,
	HOOKED_3,
	HOOKED_4,
};

class DigDug : public GameScene
{
public:
	DigDug();
	virtual ~DigDug();

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	void Initialize() override;
	void Update() override;
	void Render() const override;

	DigDug(const DigDug& obj) = delete;
	DigDug(DigDug&& obj) noexcept = delete;

	DigDug& operator=(const DigDug& obj) = delete;
	DigDug& operator=(DigDug&& obj) noexcept = delete;

private:
	void InitializeLevel();
	void InitializePlayer();
	void InitializeEnemyManager();
	void InitializeBlocks();

	void AddFPSCounter(const Point2f& p);


	TimerComponent* timer;
	unsigned int m_Sprite = 0;

	GameObject* m_pPlayer = nullptr;
	GameObject* m_EnemyManager = nullptr;
};

