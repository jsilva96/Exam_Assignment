#include "MiniginPCH.h"
#include "SoundEffect.h"
#include "ResourceManager.h"
#include <iostream>
#include "ResourceManager.h"

SoundEffect::SoundEffect(Mix_Chunk* pChunk)
	:m_pMixChunk(pChunk)
{
	if (!m_pMixChunk)
	{
		std::string error =  Mix_GetError();
	}
}
SoundEffect::~SoundEffect( )
{
	Mix_FreeChunk( m_pMixChunk );
	m_pMixChunk = nullptr;
}
void SoundEffect::SetVolume( int value )
{
	if (!m_pMixChunk) Mix_VolumeChunk( m_pMixChunk, value );
}
int SoundEffect::GetVolume( ) const
{
	if (!IsUsable()) return 0;

	if ( m_pMixChunk != nullptr ) return Mix_VolumeChunk( m_pMixChunk, -1 );
	else return -1;
}
Mix_Chunk* SoundEffect::GetChunk() const
{
	return m_pMixChunk;
}
void SoundEffect::StopAll( )
{
	Mix_HaltChannel(-1 );
}
void SoundEffect::PauseAll( )
{
	Mix_Pause( -1 );
}
void SoundEffect::ResumeAll( )
{
	Mix_Resume( -1 );
}