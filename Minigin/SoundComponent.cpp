#include "MiniginPCH.h"
#include "SoundComponent.h"
#include "SoundEffect.h"
#include "MusicManager.h"
#include "ResourceManager.h"

SoundComponent::SoundComponent()
	:m_IsVolumeChanged{ false },
    m_Volume(25)
{
}
SoundComponent::~SoundComponent()
{
	m_Volume = 25;
	m_IsVolumeChanged = false;
}
void* SoundComponent::operator new(size_t)
{
	return PoolManager::GetInstance().RetrieveObject<SoundComponent>();
}
void SoundComponent::operator delete(void* ptrDelete)
{
	PoolManager::GetInstance().ReturnObject<SoundComponent>(static_cast<BaseObject*>(ptrDelete));
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
