#pragma once
#include "BaseComponent.h"
#include "SomeStructs.h"
class TransformComponent: public BaseComponent
{
public:
	TransformComponent();
	virtual ~TransformComponent();

	void* operator new(size_t nBytes);
	void  operator delete(void* ptrDelete);

	void Initialize() override;
	void Update() override;
	void Render() const override;

	void Reset() override;

	void SetPosition(const Point2f& pos);
	Point2f GetPosition() const;

	void SetRotation(float rot);
	float GetRotation() const;

	void SetScale(float scale);
	void SetScale(const Point2f& scale);

	Point2f GetScale() const;

	void SetPivotPoint(const Point2f& p);
	Point2f GetPivotPoint() const;
	void ResetPivot();

	const TransformInfo GetTransformInfo() const;

private:
	TransformInfo m_TransformInfo;

	TransformComponent(const TransformComponent& obj) = delete;
	TransformComponent(const TransformComponent&& obj) = delete;
	TransformComponent& operator=(const TransformComponent& obj) = delete;
	TransformComponent& operator=(const TransformComponent&& obj) = delete;
};

