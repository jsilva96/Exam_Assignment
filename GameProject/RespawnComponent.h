#pragma once
#include <BaseComponent.h>
#include "SomeStructs.h"

class RespawnComponent final: public BaseComponent
{
public:
	RespawnComponent(unsigned int nrOfLives);
	virtual ~RespawnComponent();

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	void Initialize() override;
	void Update() override;
	void Render() const override;

	void Respawn();

	bool CanRespawn() const;

	void SetRespawnPos(const Point2f& p) { m_RespawnPos = p; };

	RespawnComponent(const RespawnComponent&) = delete;
	RespawnComponent(RespawnComponent&&) noexcept = delete;

	RespawnComponent& operator=(const RespawnComponent&) = delete;
	RespawnComponent& operator=(RespawnComponent&&) noexcept = delete;

private:
	unsigned int m_Lives;
	Point2f m_RespawnPos;
};

