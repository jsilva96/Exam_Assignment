#include "MiniginPCH.h"
#include "SoundComponent.h"
#include "SoundEffect.h"
#include "MusicManager.h"
#include "ResourceManager.h"

typedef std::pair<const std::string, SoundEffect*> soundString;

SoundComponent::SoundComponent()
	:m_IsVolumeChanged{ false },
    m_Volume(25)
{
}
SoundComponent::~SoundComponent()
{
}

void SoundComponent::Initialize() 
{
}
void SoundComponent::Update()
{
}
void SoundComponent::Render() const 
{
}
void SoundComponent::Reset()
{
	BaseComponent::Reset();
}
void SoundComponent::Play(unsigned int index, int loops)
{
	MusicManager::GetInstance().PlaySoundEffect(index, m_Volume, loops);
}
unsigned int SoundComponent::LoadNewSound(const std::string& path)
{
	return dae::ResourceManager::GetInstance().LoadSoundEffect(path);
}
void SoundComponent::ChangeVolume(int value)
{
	m_Volume += value;
	m_IsVolumeChanged = true;
}
