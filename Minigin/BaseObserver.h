#pragma once
#include<string>

class GameObject;
class BaseObserver
{
public:
	BaseObserver() = default;
	virtual ~BaseObserver() = default;

	virtual void onNotify(GameObject* pPlayer, unsigned int event) = 0;

	BaseObserver(const BaseObserver& obj) = delete;
	BaseObserver(BaseObserver&& obj) noexcept = delete;

	BaseObserver& operator=(const BaseObserver& obj) = delete;
	BaseObserver& operator=(BaseObserver&& obj) noexcept = delete;
};