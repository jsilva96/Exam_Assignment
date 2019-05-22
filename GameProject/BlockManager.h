#pragma once
#include <BaseComponent.h>
#include "SomeStructs.h"

//class GameObject;
class BlockManager final: public BaseComponent
{
public:
	BlockManager(int blockWidth, int blockHeight);
	virtual ~BlockManager() = default;

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	void Initialize() override;
	void Update() override;
	void Render() const override;

	void GetBlocks(float width, float height);

	void AddBlocksToScene(GameScene* pScene);
	void AddBlockCarver(const Rectf& rect);

	BlockManager(const BlockManager&) = delete;
	BlockManager(BlockManager&&) noexcept = delete;

	BlockManager& operator=(const BlockManager&) = delete;
	BlockManager& operator=(BlockManager&&) noexcept = delete;
private:

	std::vector<GameObject*> m_pBlocks;
	int m_BlockWidth, m_BlockHeight;

	GameObject* AddBlock(const Point2f& p) const;
};

