#include "SoundSystem.h"

SoundSystem::SoundSystem()
{

}

SoundSystem::~SoundSystem()
{
	ShutDown();
}

bool SoundSystem::Init()
{
	alutInit( 0, NULL );
	return true;
}

void SoundSystem::Run()
{
	typedef list< WaveSoundPtr >::iterator ite;

	ite cur = waveList_.begin();
	for( ; cur != waveList_.end(); ++ cur )
	{
		if( (*cur).unique() )
		{
			waveList_.erase( cur );
			continue;
		}

		if( (*cur)->nLoopCount_ > 0 )
		{
			int nFlag = 0;
			(*cur)->GetState( &nFlag );
			if( nFlag == AL_STOPPED || nFlag == AL_INITIAL )
			{
				-- (*cur)->nLoopCount_;
				alSourcePlay( (*cur)->source_ );
			}
		}
	}
}

void SoundSystem::ShutDown()
{
	alutExit();
}

bool SoundSystem::CreateWaveSound( const string& wsFilename, WaveSoundPtr * ppWaveSound )
{
	//创建
	ppWaveSound->reset( new WaveSound() );

	//把ppWaveSound注册到SoundSystem
	RegisterSound( *ppWaveSound );

	//初始化
	return (*ppWaveSound)->Init( wsFilename );
}

void SoundSystem::RegisterSound( WaveSoundPtr pWaveSound )
{
	waveList_.push_back( pWaveSound );
}