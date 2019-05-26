#pragma once
#include <algorithm>
#include <cmath>
#include <list>

class GameObject;
struct Point2f
{
	float x, y;

	Point2f(float x, float y)
		:x{ x },
		y{ y }
	{

	}
	Point2f()
		:x{ 0.0f },
		y{ 0.0f }
	{

	}

	Point2f& operator+=(const Point2f& p)
	{
		x += p.x;
		y += p.y;

		return *this;
	}

	Point2f& operator-=(const Point2f& p)
	{
		return (*this) += -p;
	}

	Point2f& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;

		return *this;
	}
	Point2f& operator/=(float scalar)
	{
		return (*this) *= (1 / scalar);
	}
	Point2f operator-() const
	{
		return Point2f{ -x, -y };
	}
};
struct Color4f
{
	float r, g, b, a;

	Color4f(float r, float g, float b, float a)
		:r{ r },
		g{ g },
		b{ b },
		a{ a }
	{
	}

	Color4f()
		:Color4f(1.0f, 1.0f, 1.0f, 1.0f)
	{
	}

	Color4f(float rgb)
		:Color4f(rgb, rgb, rgb, 1.0f)
	{

	}

	bool operator==(const Color4f& c) const
	{
		return ((c.r == r) && 
			    (c.g == g) && 
			    (c.b == b) && 
			    (c.a == a));
	}
};
struct Vector2f
{
	float x, y;
	Vector2f(float x, float y)
		:x{ x },
		y{ y }
	{
	}

	Vector2f()
		:Vector2f(0.0f, 0.0f)
	{
	}
	Vector2f(const Point2f& from, const Point2f& till)
		:Vector2f(till.x - from.x, till.y - from.y)
	{
	}
	Vector2f(const Point2f& p)
		:Vector2f(p.x, p.y)
	{
	}

	Vector2f& operator+=(const Vector2f& obj)
	{
		x += obj.x;
		y += obj.y;

		return *this;
	}
	Vector2f& operator-=(const Vector2f& obj)
	{
		*this += -obj;

		return (*this) += -obj;
	}

	Vector2f& operator*=(float f)
	{
		x *= f;
		y *= f;

		return *this;
	}
	Vector2f& operator/=(float f)
	{
		return (*this) *= (1 / f);
	}
	Vector2f operator-() const
	{
		return Vector2f{ -x, -y };
	}

	float Length() const { return sqrt(pow(x, 2) + pow(y, 2)); }
	Vector2f Normalize() 
	{ 
		if (Length() != 0)return Vector2f{ x, y } /= Length(); 
		return *this;
	};
	bool IsNormalized() const { return Length() == 1.0f; };
	Vector2f Orthogonal() const { return Vector2f{ -y, x }; };

	float Dot(const Vector2f& obj) { return (x * obj.x) + (y * obj.y); };
	float CrossProduct(const Vector2f& obj) { return x * obj.y - y * obj.x; };
};
struct Rectf
{
	Point2f leftBottom;
	float width;
	float height;

	Rectf(const Point2f& p, float width, float height)
		:leftBottom{ p }, 
		width{ width },
		height{ height }
	{
	}
	Rectf(float x, float y, float width, float height)
		:Rectf(Point2f(x, y), width, height)
	{
	}
	Rectf()
		:Rectf(0.0f, 0.0f, 0.0f, 0.0f)
	{
	}

	Point2f GetCenterPoint() const
	{
		return Point2f{ leftBottom.x + (width / 2), leftBottom.y + (height / 2) };
	}
};
struct TransformInfo
{
	Point2f translation{ 0.0f , 0.0f };

	Point2f scale{ 1.0f, 1.0f };

	float rotation{ 0.0f };
	Point2f Pivot;

	bool isPivotMiddle = true;

	inline void Reset()
	{
		translation = { 0.0f,0.0f };
		scale = { 1.0f, 1.0f };
		rotation = { 0.0f };
		Pivot = { 0.0f, 0.0f };

		isPivotMiddle = true;
	}
};
struct HitInfo
{
	float lambda;
	Point2f intersectPoint;
	Vector2f normal;
};
inline Vector2f operator+(Vector2f  lhs,const Vector2f& rhs)
{
	return lhs += rhs;
}
inline Vector2f operator-(Vector2f lhs, const Vector2f& rhs)
{
	return lhs + (-rhs);
}

inline Vector2f operator*(Vector2f lhs, float f)
{
	return lhs *= f;
}
inline Vector2f operator/(Vector2f lhs, float f)
{
	return lhs * (1 / f);
}

inline bool operator==(const Point2f& p1, const Point2f& p2) { return p1.x == p2.x && p1.y == p2.y; }
inline bool operator==(const Vector2f& v1, const Vector2f& v2) { return v1.x == v2.x && v1.y == v2.y; }
inline bool operator!=(const Vector2f& v1, const Vector2f& v2) { return !(v1 == v2); }
inline bool operator==(const Rectf& rect1, const Rectf& rect2) { return rect2.leftBottom == rect2.leftBottom && rect1.width == rect2.width && rect1.height == rect2.height; }
inline Point2f& operator+=(Point2f& p, const Vector2f& v)
{
	p.x += v.x;
	p.y += v.y;

	return p;
}
inline Point2f& operator-=(Point2f& p, const Vector2f& v)
{
	return p += -v;
}

template<class T>
inline bool AddCheck(std::vector<T> & container, const T& object)
{
	if (container.empty())
	{
		container.push_back(object);
		return true;
	}
	for (const T& vectorObj : container) if (vectorObj == object) return false;
	
	container.push_back(object);
	return true;
}
template<class T>
inline bool AddCheck(std::list<T> & container, const T& object)
{
	if (container.empty())
	{
		container.push_back(object);
		return true;
	}

	const auto it = std::find(container.begin(), container.end(), object);
	
	if (it != container.end())
	{
		container.push_back(object);
		return true;
	}
	else return false;
}
template<class T>
inline void DeleteCheck(T* pObject)
{	
	if (pObject)
	{
		delete pObject;
		pObject = nullptr;
	}
}
template<class T>
inline void DeleteCheck(std::vector<T*> & pContainer)
{
	for (T* pObject : pContainer)
	{
		DeleteCheck(pObject);
	}
}
template<class T> 
inline T* CastTo(GameObject* pObject)
{
	return dynamic_cast<T*>(pObject);
}

inline void GetDivisibles(std::vector<int>& v, int nr)
{
	if (nr == 0) return;

	for (int i = 1; i <= (nr / 2); i++) if (nr % i == 0) v.push_back(i);

	if (nr != 1)v.push_back(nr);
}
inline bool IsPrime(const int nr)
{
	if (nr == 1 || nr == 0) return false;

	for (int i = 2; i < (nr / 2); i++) if (nr % i == 0) return false;

	return true;
}
