#pragma once


class TransformMatrix
{
public:
	TransformMatrix();
	~TransformMatrix();


private:

	//Point2f m_Translation;

	TransformMatrix(const TransformMatrix& obj) = delete;
	TransformMatrix(const TransformMatrix&& obj) = delete;

	TransformMatrix& operator=(const TransformMatrix& obj) = delete;
	TransformMatrix& operator=(const TransformMatrix&& obj) = delete;
};

