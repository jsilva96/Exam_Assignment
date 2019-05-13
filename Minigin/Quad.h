#pragma once
#include "BaseShape.h"
class Quad : public BaseShape
{
public:
	Quad();
	virtual ~Quad() = default;

	void Initialize() override;
	void Render() const override;
	void Update() override;

	private:
	Rectf m_Rect;

	Quad(const Quad&) = delete;
	Quad(Quad&&) noexcept = delete;

	Quad& operator=(const Quad&) = delete;
	Quad& operator=(Quad&&) noexcept = delete;
};

