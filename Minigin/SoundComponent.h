#pragma once
#include "BaseComponent.h"
#include <map>
class SoundEffect;

class SoundComponent : public BaseComponent
{
public:
	SoundComponent();
	~SoundComponent();

	void Initialize() override;
	void Update() override;
	void Render() const override;

	void Reset() override;

	void Play(unsigned int index, int loops = 1);
	unsigned int LoadNewSound(const std::string& path);
	void ChangeVolume(int value);

private:
	int m_Volume;
	bool m_IsVolumeChanged;

	SoundComponent(const SoundComponent& obj) = delete;
	SoundComponent(const SoundComponent&& obj) = delete;

	SoundComponent& operator=(const SoundComponent& obj) = delete;
	SoundComponent& operator=(const SoundComponent&& obj) = delete;
};

