#pragma once
#include <GameScene.h>
struct Point2f;

enum GAME_MODE : unsigned int
{
	SOLO,
	COOP,
	VERSUS
};

class MenuScene final: public GameScene
{
public:
	MenuScene();
	virtual ~MenuScene() = default;

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	void Initialize() override;
	void Update() override;
	void Render() const override;

	void Select();

	MenuScene(const MenuScene&) = delete;
	MenuScene(MenuScene&&) noexcept = delete;

	MenuScene& operator=(const MenuScene&) = delete;
	MenuScene& operator=(MenuScene&&) noexcept = delete;
private:
	void InitializeBackground();
	void InitializeGameName();
	void InitializeOption(const std::string& text, const Point2f& p, const GAME_MODE& gameMode);
	void AddPlayer();

	void SelectGameMode();

	std::vector<GameObject*> m_Options;
	bool m_IsSelected;
};

