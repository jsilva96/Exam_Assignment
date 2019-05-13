#include "MiniginPCH.h"
#include "SoundStream.h"
#include <iostream>

SoundStream::SoundStream(Mix_Music* pMusic)
	:m_pMixMusic{ pMusic }
{
}
SoundStream::~SoundStream( )
{
	Mix_FreeMusic( m_pMixMusic );
	m_pMixMusic = nullptr;
}
bool SoundStream::Play(bool repeat )
{
	if (m_pMixMusic)
	{
		int result{ Mix_PlayMusic( m_pMixMusic, repeat ? -1 : 1 ) };
		return result == 0 ? true : false;
	}
	else return false;
	
}
void SoundStream::Stop( )
{
	Mix_HaltMusic( );
}
void SoundStream::Pause( )
{
	Mix_PauseMusic( );
}
void SoundStream::Resume( )
{
	Mix_ResumeMusic( );
}
int SoundStream::GetVolume( )
{
	return Mix_VolumeMusic( -1 );
}
bool SoundStream::IsPlaying( )
{
	return Mix_PlayingMusic( ) == 0 ? false : true;
}
Mix_Music* SoundStream::GetMusic() const
{
	return m_pMixMusic;
}
void SoundStream::SetVolume( int value )
{
	Mix_VolumeMusic( value );
}

