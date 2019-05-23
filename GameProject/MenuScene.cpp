#include "pch.h"
#include "MenuScene.h"

#include "PoolManager.h"
#include "GameObject.h"

#include "RenderComponent.h"
#include "TextComponent.h"
#include "SelectionComponent.h"
#include "InputComponent.h"
#include "SelectCommand.h"

MenuScene::MenuScene()
	:GameScene("MenuScene")
{
}

void* MenuScene::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<MenuScene>();
}
void MenuScene::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<MenuScene>(static_cast<BaseObject*>(ptrDelete));
}
void MenuScene::Initialize()
{
	InitializeBackground();
	InitializeGameName();

	Point2f p{140.0f, 350.0f};
	InitializeOption("Solo", p);

	p.y -= 40.0f;
	InitializeOption("Co-op", p);

	p.y -= 40.0f;
	InitializeOption("Versus", p);

	bool isSelected{ true };
	for(auto& obj : m_Options)
	{
		obj->GetComponent<SelectionComponent>()->SetSelected(isSelected);
		isSelected = false;
	}

	AddPlayer();
}
void MenuScene::Update()
{
}
void MenuScene::Render() const
{
}
void MenuScene::InitializeBackground()
{
	auto go = new GameObject();

	auto r = new RenderComponent();
	r->SetTexture("Textures/DigDug/Background.png");

	go->AddComponent(r);

	Add(go);
}
void MenuScene::InitializeGameName()
{
	auto go = new GameObject();

	auto t = new TextComponent();
	t->SetFont("Lingua.otf", 50);
	t->SetText("DigDug");

	go->AddComponent(t);

	go->SetPosition(140.0f, 400.0f);

	Add(go);
}
void MenuScene::InitializeOption(const std::string& text, const Point2f& p)
{
	auto go = new GameObject();

	auto t = new TextComponent();
	t->SetFont("Lingua.otf", 25);
	t->SetText(text);
	go->AddComponent(t);

	auto select = new SelectionComponent();
	go->AddComponent(select);
	go->SetPosition(p.x, p.y);


	m_Options.push_back(go);
	Add(go);
}

void MenuScene::AddPlayer()
{
	auto go = new GameObject();

	auto input = new InputComponent();

	InputOptions options;
	options.controller = ControllerButton::DPad_Down;
	options.keyboard = KeyboardButton::Down;

	auto cmd = new SelectCommand();

	for (auto& pObj : m_Options) cmd->AddOption(pObj->GetComponent<SelectionComponent>());
	input->AddCommand(cmd, options);

	go->AddComponent(input);

	Add(go);
}
