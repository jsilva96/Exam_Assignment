#pragma once
#include <map>
class SoundStream;
class SoundEffect;
class MusicManager
{
public:
	static MusicManager& GetInstance();
	void Destroy();
    ~MusicManager();
	
	void Update();
	unsigned int LoadEffect(const std::string& path);
    unsigned int LoadStream(const std::string& path);
	
	void ChangeVolume(int value);

	void PlaySoundEffect(unsigned int index, int volume, int loops = 0);
	void PlaySoundStream(unsigned int index, int volume, bool repeat = false);


private:
	static MusicManager * m_pInstance;
	bool m_IsVolumeChanged;

	MusicManager();


	std::map<std::string, unsigned int> m_Paths;
	std::map<unsigned int, SoundStream*> m_SoundStreams;
	std::map<unsigned int, SoundEffect*> m_SoundEffects;


	static int m_Volume;

	MusicManager(const MusicManager& obj) = delete;
	MusicManager(const MusicManager&& obj) = delete;

	MusicManager& operator=(const MusicManager& obj) = delete;
	MusicManager& operator=(const MusicManager&& obj) = delete;
};

