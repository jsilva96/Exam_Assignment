#include "pch.h"
#include "FPSScene.h"

#include "GameObject.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "Texture2D.h"
#include "TextComponent.h"
#include "PoolManager.h"
#include "Time.h"

FPSScene::FPSScene()
{
}

void* FPSScene::operator new(size_t nBytes)
{
	UNREFERENCED_PARAMETER(nBytes);
	return PoolManager::GetInstance().RetrieveObject<FPSScene>();
}
void FPSScene::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject(static_cast<BaseObject*>(ptrDelete));
}
void FPSScene::Initialize()
{
	//BACKGROUND
	m_pBackground = new GameObject();

	auto r = new RenderComponent();
	r->SetTexture("background.jpg");
	m_pBackground->AddComponent(r);

	Add(m_pBackground);

	//DAE LOGO
	m_pDAEText = new GameObject();

	r = new RenderComponent();
	r->SetTexture("logo.png");
	m_pDAEText->AddComponent(r);

	auto windowRect = dae::Renderer::GetInstance().GetWindowDims();
	auto text = r->GetTexture();

	auto wHalfWidth = windowRect.width / 2;
	auto wHalfHeight = windowRect.width / 2;

	auto tHalfWidth = text->GetWidth() / 2;
	auto tHalfHeight = text->GetHeight() / 2;

	m_pDAEText->GetTransform()->SetPosition({ wHalfWidth - tHalfWidth, wHalfHeight - tHalfHeight });

	Add(m_pDAEText);

    //FPSDisplay
	m_pFPS = new GameObject();

	m_pFPSText = new TextComponent();
	m_pFPSText->SetFont("Lingua.otf", 25);
	m_pFPSText->SetColor({ 0, 1, 0,1 });
	m_pFPSText->SetText("FPS");

	m_pFPS->GetTransform()->SetPosition({ 0,windowRect.height - 25 });
	m_pFPS->AddComponent(m_pFPSText);

	Add(m_pFPS);
}
void FPSScene::Update()
{
	std::string fps{ "FPS :" };

	if(m_pFPS)m_pFPSText->SetText(fps += to_string(Time::GetInstance().GetFPS()));
}
