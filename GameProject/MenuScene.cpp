#include "pch.h"
#include "MenuScene.h"

#include "PoolManager.h"
#include "GameObject.h"

#include "SceneManager.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "SelectionComponent.h"
#include "InputComponent.h"
#include "SelectCommand.h"
#include "EventsAndTags.h"
#include "DigDug.h"
#include "EnterCommand.h"

MenuScene::MenuScene()
	:GameScene(MENU), m_IsSelected(false)
{
}

void* MenuScene::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<MenuScene>();
}
void MenuScene::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<MenuScene>(ptrDelete);
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
	if (m_IsSelected) SelectGameMode();
}
void MenuScene::Render() const
{
}
void MenuScene::Select()
{
	m_IsSelected = true;
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
	input->AssignGamepad(5);

	InputOptions options;
	options.controller = ControllerButton::DPad_Down;
	options.keyboard = KeyboardButton::Down;

	auto cmd = new SelectCommand(true);

	for (auto& pObj : m_Options) cmd->AddOption(pObj->GetComponent<SelectionComponent>());
	input->AddCommand(cmd, options);

	options.controller = ControllerButton::DPad_Up;
	options.keyboard = KeyboardButton::Up;
	cmd = new SelectCommand(false);
	
	for (auto& pObj : m_Options) cmd->AddOption(pObj->GetComponent<SelectionComponent>());
	input->AddCommand(cmd, options);

	options.controller = ControllerButton::ButtonA;
	options.keyboard = KeyboardButton::Enter;

	input->AddCommand(new EnterCommand(), options);

	go->AddComponent(input);

	Add(go);
}

void MenuScene::SelectGameMode()
{
	const auto it = std::find_if(m_Options.begin(), m_Options.end(), [](GameObject* pObj)
	{
		return pObj->GetComponent<SelectionComponent>()->IsSelected();
	});

	if (it == m_Options.end()) throw std::runtime_error("MenuScene::SelectGameMode->No GameMode found/n");

	auto scene = new DigDug();

	SceneManager::GetInstance().AddScene(scene);
	SceneManager::GetInstance().SetScene(scene->GetID());
}
