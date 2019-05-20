#include "MiniginPCH.h"
#include "MusicManager.h"
#include "SoundStream.h"
#include "PoolManager.h"
#include "SoundEffect.h"

MusicManager* MusicManager::m_pInstance = nullptr;
int MusicManager::m_Volume = 25;

MusicManager::MusicManager()
	:m_IsVolumeChanged{ false }
{
}
MusicManager::~MusicManager()
{
	for (auto stream : m_SoundStreams) PoolManager::GetInstance().ReturnObject<SoundStream>(stream.second);

	for (auto effect : m_SoundEffects) PoolManager::GetInstance().ReturnObject<SoundEffect>(effect.second);
}
MusicManager& MusicManager::GetInstance()
{
	if (!m_pInstance) m_pInstance = new MusicManager();
	return *m_pInstance;
}
void MusicManager::Destroy()
{
	if (m_pInstance) delete m_pInstance;
}
void MusicManager::Update()
{
	if (!m_IsVolumeChanged)return;
	
		SoundStream::SetVolume(m_Volume);
		m_IsVolumeChanged = false;
}

unsigned int MusicManager::LoadEffect(const std::string& path)
{
	auto it = m_Paths.find(path);
	if (it != m_Paths.end()) return (*it).second;

	auto chunk = Mix_LoadWAV(path.c_str());
	if (!chunk) throw std::runtime_error("MusicManager::LoadEffect-> Failed to load effect. Path ->" + path + '\n');

	unsigned int id =(unsigned int) m_SoundEffects.size() + 1;

	m_SoundEffects[id] = new SoundEffect(chunk);

	return id;
}
unsigned int MusicManager::LoadStream(const std::string& path)
{
	auto it = m_Paths.find(path);
	if (it != m_Paths.end()) return (*it).second;

	auto music = Mix_LoadMUS(path.c_str());
	if (!music) throw std::runtime_error("MusicManager::LoadStream-> Failed to load stream. Path ->" + path + '\n');

	unsigned int id =(unsigned int) m_SoundStreams.size() + 1;

	m_SoundStreams[id] = new SoundStream(music);

	return int(id);
}
void MusicManager::ChangeVolume(int value)
{
	m_Volume += value;

	m_IsVolumeChanged = true;
}
void MusicManager::PlaySoundEffect(unsigned index, int volume,int loops)
{
	auto it = m_SoundEffects.find(index);
	if (it == m_SoundEffects.end()) return;

	auto soundEffect = (*it).second;

	if (!soundEffect->IsUsable()) return;

	soundEffect->SetVolume(volume);
	Mix_PlayChannel(-1, soundEffect->GetChunk(), loops);
}

void MusicManager::PlaySoundStream(unsigned index, int volume, bool repeat)
{
	auto it = m_SoundStreams.find(index);
	if (it == m_SoundStreams.end()) return;

	auto soundStream = (*it).second;

	if (!soundStream->IsUsable()) return;

	soundStream->SetVolume(volume);
	Mix_PlayMusic(soundStream->GetMusic(), repeat ? -1 : 1);
}
