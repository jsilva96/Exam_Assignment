#include "pch.h"
#include "DigDug.h"

#include "PoolManager.h"

#include "GameObject.h"
#include "RenderComponent.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "SpriteDescSwitchComponent.h"
#include "TimerComponent.h"
#include <iostream>
#include "EnemyManager.h"
#include "FPSDisplayComponent.h"
#include "TextComponent.h"
#include "BlockManager.h"

#include "MenuScene.h"

#include "InputComponent.h"
#include "PlayerMovementComponent.h"
#include "TranslationComponent.h"
#include "PlayerSpriteSwitchComponent.h"
#include "ColliderComponent.h"
#include "PlayerCollisionHandler.h"
#include "EventsAndTags.h"
#include "PlayerManager.h"

DigDug::DigDug(unsigned int gameMode)
	:GameScene(SCENE::DIG_DUG), m_GameMode(gameMode)
{
}
DigDug::~DigDug()
{
}
void* DigDug::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<DigDug>();
}
void DigDug::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<DigDug>(ptrDelete);
}

void DigDug::Initialize()
{
	InitializeLevel();
//	InitializeBlocks();
	InitializePlayer();
	InitializeEnemyManager();

	switch (m_GameMode)
	{
	case SOLO:
		InitializeSolo();
		break;

	case COOP:
		InitializeCoop();
		break;

	case VERSUS:
		InitializeVersus();
		break;

	default:
		throw std::exception("DigDug::Initialize->GameMode unknown\n");
		break;
	}

//	InitializeFygar();
//	InitializePooka();


	AddFPSCounter({ 0.0f, 0.0f });
}

void DigDug::InitializeSolo()
{
	Add(m_pPlayerManager->GetComponent<PlayerManager>()->GetPlayer({ 200.0f, 230.0f }));
}
void DigDug::InitializeCoop()
{
	Add(m_pPlayerManager->GetComponent<PlayerManager>()->GetPlayer({ 160.0f, 230.0f }));
	Add(m_pPlayerManager->GetComponent<PlayerManager>()->GetPlayer({ 240.0f, 230.0f }));
}
void DigDug::InitializeVersus()
{
	Add(m_pPlayerManager->GetComponent<PlayerManager>()->GetPlayer({ 200.f, 230.0f }));
	Add(m_EnemyManager->GetComponent<EnemyManager>()->GetPlayableFygar({ 40.0f, 380.0f }));
}
void DigDug::Update()
{
}
void DigDug::Render() const
{
}
void DigDug::InitializeLevel()
{
	auto go = new GameObject();

	auto r = new RenderComponent();
	r->SetTexture("Levels/DigDug/Level1.png");

	r->SetFlipped(false, false);
	go->GetTransform()->SetScale(1.0f);
	go->AddComponent(r);

	Add(go);
}
void DigDug::InitializePlayer()
{
	m_pPlayerManager = new GameObject();
	m_pPlayerManager->AddComponent(new PlayerManager());

	Add(m_pPlayerManager);
}
void DigDug::InitializeEnemyManager()
{
    m_EnemyManager = new GameObject();

	auto r = new EnemyManager();
	m_EnemyManager->AddComponent(r);

	Add(m_EnemyManager);
}
void DigDug::InitializeBlocks()
{
	int blockScale{ 4 };
	std::vector<Rectf> carvers;
	auto go = new GameObject();

	auto blockManager = new BlockManager(2 * blockScale, 2 * blockScale);
	go->AddComponent(blockManager);

	blockManager->GetBlocks(450, (544 - 76));

	carvers.push_back({ 37,290,20,153 });
	carvers.push_back({ 164,320,89,22 });
	carvers.push_back({ 294,165,121,25 });
	carvers.push_back({ 192,290,25, 200 });
	carvers.push_back({ 70,420,115, 25 });
	carvers.push_back({ 292,512,25, 150 });


	for (auto rect : carvers)
	{
		rect.leftBottom.y = (544 - rect.leftBottom.y) + rect.height;
		blockManager->AddBlockCarver(rect);
	}

	blockManager->AddBlocksToScene(this);

	Add(go);
}
void DigDug::AddFPSCounter(const Point2f& p)
{
 	auto go = new GameObject();
	auto fps = new FPSDisplayComponent();
	auto t = new TextComponent();

	fps->SetTextComponent(t);

	go->AddComponent(t);
	go->AddComponent(fps);

	t->SetFont("Lingua.otf", 15);
	t->SetColor({ 0.0f, 1.0f, 0.0f, 1.0f });
	go->SetPosition(p.x, p.y);

	Add(go);
}
