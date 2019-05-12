#pragma once
#include "RenderComponent.h"

enum class SpriteParse
{
	HORIZONTAL,
	VERTICAL,
	CUSTOM
};

struct SpriteDesc
{
	Point2f startPos = { 0.0f, 0.0f };
	unsigned int frames;
	int nrOfRuns;  //for infinite runs, use 0 or less;
	float width;
	float height;
	float frameTime;
	SpriteParse parseLogic;

	SpriteDesc(const Point2f& startPos,unsigned int frames, int nrOfRuns, float width, float height, float frameTime, SpriteParse parseLogic)
		:startPos{ startPos },
		frames{ frames },
		width{ width },
		height{ height },
		frameTime{ frameTime },
		parseLogic{ parseLogic },
	    nrOfRuns(nrOfRuns)
	{
	}
	SpriteDesc()
		:SpriteDesc({0.0f, 0.0f}, 0, -1, 0.0f, 0.0f, 0.0f, SpriteParse::HORIZONTAL)
	{
	}

	bool operator==(const SpriteDesc& obj) const
	{


		return (obj.startPos == startPos) &&
			(obj.nrOfRuns == nrOfRuns) &&
			(obj.frameTime == frameTime) &&
			(obj.height == height) &&
			(obj.width == width) &&
			(obj.parseLogic == parseLogic) &&
			(obj.frames == frames);

 
	}

	inline void Reset()
	{
		startPos = { 0.0f, 0.0f };
		frames = 0;
		width = 0.0f;
		height = 0.0f;
		parseLogic = SpriteParse::HORIZONTAL;
		nrOfRuns = 0;
	}
};


class SpriteComponent final : public RenderComponent
{
public:
	SpriteComponent(const SpriteDesc& desc);
	SpriteComponent();
	~SpriteComponent();

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	void Initialize() override;
	void Update() override;
	void Render() const override;

	void SetTexture(const string& filename) override;
	void StopTimer(bool b = true);
	void SetDesc(const SpriteDesc& desc);

protected:
	virtual void UpdateCustom() {};
	void UpdateHorizontal();
	void UpdateVertical();

	SpriteDesc m_SpriteInfo;
	Rectf m_SrcRect;
	unsigned int m_CurrFrame;
	float m_Timer;
	bool m_StopTimer;
	
	bool m_CountRuns;
	unsigned int m_RunCount;
private:

	SpriteComponent(const SpriteComponent&) = delete;
	SpriteComponent(SpriteComponent&&) noexcept = delete;

	SpriteComponent& operator=(const SpriteComponent&) = delete;
	SpriteComponent& operator=(SpriteComponent&&) noexcept = delete;
};

