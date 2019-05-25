#pragma once
#include <BaseComponent.h>
#include "SomeStructs.h"

class PlayerManager final: public BaseComponent
{
public:
	PlayerManager() = default;
	virtual ~PlayerManager() = default;

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	void Initialize() override;
	void Update() override;
	void Render() const override;

	PlayerManager(const PlayerManager&) = delete;
	PlayerManager(PlayerManager&&) noexcept = delete;

	PlayerManager& operator=(const PlayerManager&) = delete;
	PlayerManager& operator=(PlayerManager&&) noexcept = delete;

	GameObject* GetPlayer(const Point2f& p);

private:
	int m_NrOfPlayersSpawned = 0;
};

