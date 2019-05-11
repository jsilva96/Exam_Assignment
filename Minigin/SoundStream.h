#pragma once
#include <string>
#include "BaseObject.h"

class SoundStream   :  public BaseObject
{
public:
	SoundStream( Mix_Music* pMusic );
	~SoundStream();

	bool Play( bool repeat );
		
	static void Stop( );
	static void Pause( );
	static void Resume( );
	
	static void SetVolume(int value );
	static int GetVolume( );
	
	static bool IsPlaying( );

	void Reset() override;

	Mix_Music* GetMusic() const;
private:
	Mix_Music *m_pMixMusic;
	int m_Volume;

	SoundStream(const SoundStream& other) = delete;
	SoundStream(const SoundStream&& other) = delete;

	SoundStream& operator=(const SoundStream& rhs) = delete;
	SoundStream& operator=(const SoundStream&& rhs) = delete;
};