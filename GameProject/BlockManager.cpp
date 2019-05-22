#include "pch.h"
#include "BlockManager.h"
#include "PoolManager.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "GameScene.h"
#include "GameObject.h"

#include <vector>
#include "ColliderComponent.h"
#include "BlockCollisionHandler.h"
#include "EventsAndTags.h"

BlockManager::BlockManager(int blockWidth, int blockHeight)
	:m_BlockWidth(blockWidth), m_BlockHeight(blockHeight)
{
}
void* BlockManager::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<BlockManager>();
}
void BlockManager::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<BlockManager>(static_cast<BaseObject*>(ptrDelete));
}
void BlockManager::Initialize()
{
}
void BlockManager::Update()
{
}
void BlockManager::Render() const
{
}
void BlockManager::GetBlocks(float width, float height)
{
	Point2f p{};

	int nrOfColumns{ int(width / m_BlockWidth) + 1 };
	int nrOfRows{ int(height / m_BlockHeight)  + 1};
	int nColumns{};

	int nrOfBlocks = nrOfColumns * nrOfRows;

	for (int i = 0; i < nrOfBlocks; i++)
	{
		m_pBlocks.push_back(AddBlock(p));

		p.x += m_BlockWidth;

		++nColumns;
		if(nColumns == nrOfColumns)
		{
			nColumns = 0;
			p.x = 0.0f;
			p.y += m_BlockHeight;
		}
	}
}

void BlockManager::AddBlocksToScene(GameScene* pScene)
{
	for (auto& pObj : m_pBlocks) pScene->Add(pObj);
}

void BlockManager::AddBlockCarver(const Rectf& rect)
{
	auto go = new GameObject();
	auto c = new ColliderComponent();
	auto handler = new BaseCollisionHandler();
	c->SetRectf(rect);
	c->AddHandler(handler);
	c->SetStatic(true);

	go->AddComponent(c);
	go->AddComponent(handler);

	go->AddTag(BLOCK_CARVER);

	go->SetPosition(rect.leftBottom.x, rect.leftBottom.y);

	m_pBlocks.push_back(go);
}

GameObject* BlockManager::AddBlock(const Point2f& p) const
{
	auto go = new GameObject();
	auto r = new RenderComponent();
	r->SetTexture("Textures/DigDug/Black_Sprite.png");

	go->AddComponent(r);
	go->SetPosition(p.x, p.y);
	go->GetTransform()->SetScale(4);

	r->SetActive(false);

	Rectf rect{ p, float(m_BlockWidth - 0.5f),float(m_BlockHeight - 0.5f)};

	auto c = new ColliderComponent(rect);
	c->SetStatic(true);

	go->AddComponent(c);

	auto handler = new BlockCollisionHandler();
	go->AddComponent(handler);
	c->AddHandler(handler);

	go->AddTag(BLOCK);

	return go;
}
