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

#include "InputComponent.h"
#include "PlayerMovementComponent.h"
#include "TranslationComponent.h"
#include "PlayerSpriteSwitchComponent.h"
#include "ColliderComponent.h"
#include "PlayerCollisionHandler.h"
#include "EventsAndTags.h"

DigDug::DigDug()
{
}
DigDug::~DigDug()
{
}

void* DigDug::operator new(size_t nBytes)
{
	return PoolManager::GetInstance().RetrieveObject<DigDug>();
}
void DigDug::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<DigDug>(static_cast<BaseObject*>(ptrDelete));
}

void DigDug::Initialize()
{
	InitializeLevel();
	InitializeBlocks();
	InitializePlayer();
//	InitializeFygar();
//	InitializePooka();


	AddFPSCounter({ 0.0f, 0.0f });
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
	go->GetTransform()->SetScale(2.0f);
	go->AddComponent(r);

	Add(go);
}
void DigDug::InitializePlayer()
{
	Point2f pos{ 30.0f, 30.0f };
	float scale{ 1.0f };
	m_pPlayer = new GameObject();

	//SPRITE COMPONENT
	SpriteDesc desc;
	desc.width = 14.0f;
	desc.height = 13.0f;
	desc.parseLogic = SpriteParse::HORIZONTAL;
	desc.frames = 1;
	desc.frameTime = 1 / 10.0f;
	desc.startPos = { 0.0f, 0.0f};
	desc.nrOfRuns = -1;

	auto s = new SpriteComponent(desc);
	s->SetTexture("Textures/DigDug/Player_Sprite.png");

	m_pPlayer->AddComponent(s);
	s->SetFlipped(true, false);

	//PLAYER MOVEMENT COMPONENT
	auto movCmp = new PlayerMovementComponent(30.0f);
	auto input = new InputComponent();
	auto trans = new TranslationComponent();

	movCmp->SetInputComponent(input);
	movCmp->SetTranslationComponent(trans);

	m_pPlayer->AddComponent(input);
	m_pPlayer->AddComponent(trans);
	m_pPlayer->AddComponent(movCmp);

	//PLAYER SPRITE SWITCH COMPONENT
	auto pSwitch = new PlayerSpriteSwitchComponent();
	pSwitch->SetSpriteComponent(s);
	pSwitch->SetTranslationComponent(trans);

	m_pPlayer->AddComponent(pSwitch);

	//COLLIDER
	auto c = new ColliderComponent();
	Rectf rect{ pos, desc.width * scale, desc.height * scale};
	c->SetRectf(rect);
	c->SetStatic(false);

	auto handler = new PlayerCollisionHandler();
	c->AddHandler(handler);

	m_pPlayer->AddComponent(c);
	m_pPlayer->AddComponent(handler);


	m_pPlayer->SetPosition(pos.x, pos.y);
	m_pPlayer->GetTransform()->SetScale(scale);
	m_pPlayer->AddTag(TAG::PLAYER);

	Add(m_pPlayer);
}
void DigDug::InitializeEnemyManager()
{
	auto go = new GameObject();

	auto r = new EnemyManager();
	go->AddComponent(r);

	Add(go);
}
void DigDug::InitializeBlocks()
{
	int scale{ 2 };
	int blockScale{ 1 };
	auto go = new GameObject();

	auto blockManager = new BlockManager(8 * blockScale, 8 * blockScale);
	go->AddComponent(blockManager);

	blockManager->GetBlocks(225 * scale, (272 - 38) * scale);
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

	t->SetFont("Lingua.otf", 25);
	t->SetColor({ 0.0f, 1.0f, 0.0f, 1.0f });
	go->SetPosition(p.x, p.y);

	Add(go);
}
