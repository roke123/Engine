#include "WaveSound.h"

WaveSound::WaveSound() : nPlayOffset_( 0 ),
	nLoopCount_( 0 )
{
	memset( sourcePos_, 0, sizeof( ALfloat ) * 3 );
	memset( sourceVel_, 0, sizeof( ALfloat ) * 3 );
	memset( listenerPos_, 0, sizeof( ALfloat ) * 3 );
	memset( listenerVel_, 0, sizeof( ALfloat ) * 3 );
}

WaveSound::~WaveSound()
{
	ShutDown();
}

void WaveSound::SetVolume( ALfloat dwVolume )
{
	alSourcef( source_, AL_GAIN, dwVolume );
}

float WaveSound::GetVolume()
{
	float fVolume;
	alGetSourcefv( source_, AL_GAIN, &fVolume );
	return fVolume;
}

//取得
void WaveSound::GetState( int * nFlag )
{
	alGetSourcei( source_, AL_SOURCE_STATE, (ALint *)nFlag);
}

int WaveSound::Play( int nLoopCount, int nPlayOffset )
{
	int nFlag = 0;
	GetState( &nFlag );
	if( nFlag != AL_STOPPED && nFlag != AL_INITIAL )
		return nFlag;

	nLoopCount_ = nLoopCount;
	nPlayOffset_ = nPlayOffset;

	return nFlag;
}

//bFlag = true停止，false恢复
int WaveSound::Pause( bool bFlag )
{
	int nFlag = 0;
	GetState( &nFlag );
	if( nFlag == AL_PAUSED && !bFlag )
		alSourcePlay( source_ );
	else if( nFlag == AL_PLAYING && bFlag )
		alSourcePause( source_ );

	return nFlag;
}

//SOUND_STOP_RELEASE为播放完成当前一个循环后停止
//SOUND_STOP_IMMEDIATE为立刻停止声音
void WaveSound::Stop( int nFlag )
{
	if( nFlag == SOUND_STOP_IMMEDIATE )
	{
		nLoopCount_ = 0;
		alSourceStop( source_ );
	}
	else
	{
		//设置为最后一次循环
		nLoopCount_ = 1;
	}
}

//初始化函数,载入文件
bool WaveSound::Init( const string& wsFilename )
{
	ALenum format;
	ALsizei size;
	ALvoid * data;
	ALsizei freq;
	ALboolean loop;

	// 载入WAV数据
	alGenBuffers( 1, &sourceData_ );
	if (alGetError() != AL_NO_ERROR)
		return AL_FALSE;

	alutLoadWAVFile( const_cast<char*>(wsFilename.c_str()), &format, &data, &size, &freq, &loop);
	alBufferData( sourceData_, format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

	if (alGetError() != AL_NO_ERROR)
		return AL_FALSE;

	alGenSources( 1, &source_ );

	alSourcei ( source_, AL_BUFFER, sourceData_ );
	alSourcef ( source_, AL_PITCH, 1.0f );
	alSourcef ( source_, AL_GAIN,     1.0f     );
	alSourcefv( source_, AL_POSITION, sourcePos_);
	alSourcefv( source_, AL_VELOCITY, sourceVel_);
	alSourcei ( source_, AL_LOOPING,  loop );

	alListenerfv( AL_POSITION, listenerPos_ );
	alListenerfv( AL_VELOCITY, listenerVel_ );

	// 做错误检测并返回
	if (alGetError() != AL_NO_ERROR)
		return AL_FALSE;

	return AL_TRUE;
}

//卸载当前声音
void WaveSound::ShutDown()
{
	alDeleteBuffers(1, &sourceData_ );
	alDeleteSources(1, &source_ );
	nLoopCount_ = 0;
	nPlayOffset_ = 0;
}