#pragma once
#include <string>
#include "BaseObject.h"

class SoundEffect final :  public BaseObject
{
public:
	SoundEffect(Mix_Chunk* pChunk);
	~SoundEffect( );

	bool Play( int loops );

	void SetVolume( int value );
	int GetVolume( ) const; 

	Mix_Chunk* GetChunk() const;

	static void StopAll( );
	static void PauseAll( );
	static void ResumeAll( );
private:
	Mix_Chunk* m_pMixChunk;

	SoundEffect(const SoundEffect& other) = delete;
	SoundEffect(const SoundEffect&& other) = delete;

	SoundEffect& operator=(const SoundEffect& rhs) = delete;
	SoundEffect& operator=(const SoundEffect&& rhs) = delete;
};
