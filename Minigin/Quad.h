#pragma once
#include "BaseShape.h"
class Quad : public BaseShape
{
public:
	Quad();
	virtual ~Quad() {};

	void Initialize() override;
	void Render() const override;
	void Update() override;
	void Reset() override;
private:
	Rectf m_Rect;

	Quad(const Quad& obj) = delete;
	Quad(const Quad&& obj) = delete;

	Quad& operator=(const Quad& obj) = delete;
	Quad& operator=(const Quad&& obj) = delete;
};

