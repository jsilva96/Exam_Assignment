#pragma once
#include "GameObject.h"
#include "SomeStructs.h"

class BaseShape : public GameObject
{
public:
	BaseShape(unsigned int nrOfVerts);

	virtual ~BaseShape();

	void Initialize() override;
	void Update() override;
	void Render() const override;

	void SetLength(float length);
	void SetColor(const Color4f& c);
	
	void OnCollide(GameObject* pObj) override;
	void OnLevelCollide(HitInfo info) override;

protected:
	std::vector<Point2f> m_Verts;
	Color4f m_Color;
	unsigned int m_NrOfVerts;
	float m_Length;
private:
	BaseShape(const BaseShape&) = delete;
	BaseShape(BaseShape&&) noexcept = delete;

	BaseShape& operator=(const BaseShape&) = delete;
	BaseShape& operator=(BaseShape&&) noexcept = delete;
};
