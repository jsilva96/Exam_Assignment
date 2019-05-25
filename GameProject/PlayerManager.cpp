#include "pch.h"
#include "PlayerManager.h"

#include "PoolManager.h"

#include "SpriteComponent.h"
#include "InputComponent.h"
#include "PlayerMovementComponent.h"
#include "PlayerSpriteSwitchComponent.h"
#include "ColliderComponent.h"
#include "PlayerCollisionHandler.h"
#include "TranslationComponent.h"
#include "TransformComponent.h"
#include "EventsAndTags.h"

void* PlayerManager::operator new(size_t nBytes)
{
	return PoolManager::GetInstance().RetrieveObject<PlayerManager>();
}
void PlayerManager::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<PlayerManager>(ptrDelete);
}
void PlayerManager::Initialize()
{
}
void PlayerManager::Update()
{
}
void PlayerManager::Render() const
{
}

GameObject* PlayerManager::GetPlayer(const Point2f& p)
{
	if (m_NrOfPlayersSpawned == 2) return nullptr;
	float scale{ 1.0f };
	
	auto obj = new GameObject();

	//SPRITE COMPONENT
	SpriteDesc desc;
	desc.width = 14.0f;
	desc.height = 13.0f;
	desc.parseLogic = SpriteParse::HORIZONTAL;
	desc.frames = 1;
	desc.frameTime = 1 / 10.0f;
	desc.startPos = { 0.0f, 0.0f };
	desc.nrOfRuns = -1;

	auto s = new SpriteComponent(desc);
	s->SetTexture("Textures/DigDug/Player_Sprite.png");

	obj->AddComponent(s);
	s->SetFlipped(true, false);

	//PLAYER MOVEMENT COMPONENT
	auto movCmp = new PlayerMovementComponent(30.0f);
	auto input = new InputComponent();
	auto trans = new TranslationComponent();

	input->AssignGamepad(m_NrOfPlayersSpawned);

	movCmp->SetInputComponent(input);
	movCmp->SetTranslationComponent(trans);

	obj->AddComponent(input);
	obj->AddComponent(trans);
	obj->AddComponent(movCmp);

	//PLAYER SPRITE SWITCH COMPONENT
	auto pSwitch = new PlayerSpriteSwitchComponent();
	pSwitch->SetSpriteComponent(s);
	pSwitch->SetTranslationComponent(trans);

	obj->AddComponent(pSwitch);

	//COLLIDER
	auto c = new ColliderComponent();
	Rectf rect{ p, desc.width * scale, desc.height * scale };
	c->SetRectf(rect);
	c->SetStatic(false);

	auto handler = new PlayerCollisionHandler();
	c->AddHandler(handler);

	obj->AddComponent(c);
	obj->AddComponent(handler);


	obj->SetPosition(p.x, p.y);
	obj->GetTransform()->SetScale(scale);
	obj->AddTag(TAG::PLAYER);

	++m_NrOfPlayersSpawned;

	return obj;
}
