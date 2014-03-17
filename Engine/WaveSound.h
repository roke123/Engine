#ifndef __WAVESOUND_H__
#define __WAVESOUND_H__

#include <AL\al.h>
#include <AL\alc.h>
#include <AL\alut.h>
#include <string>
#include <D2D1.h>
#include <memory>
using namespace std;

enum SOUNDSTOPFLAG
{
	SOUND_STOP_RELEASE = 0,
	SOUND_STOP_IMMEDIATE = 1
};

class WaveSound
{
	friend class SoundSystem;
public:
	//析构函数
	
	~WaveSound();

	void SetVolume( ALfloat dwVolume );

	float GetVolume();

	//取得
	void GetState( int * dwFlag );

	int Play( int nLoopCount = 1, int nPlayOffset = 0 );

	//bFlag = true停止，false恢复
	int Pause( bool bFlag = true );

	//SOUND_STOP_RELEASE为播放完成当前一个循环后停止
	//SOUND_STOP_IMMEDIATE为立刻停止声音
	void Stop( int nFlag = SOUND_STOP_IMMEDIATE );

private:
	//构造函数
	WaveSound();

	//初始化函数,载入文件
	bool Init( const string& wsFilename );

	//卸载当前声音
	void ShutDown();

private:
	//声音源位置和速度（暂不用）
	ALfloat sourcePos_[3];
	ALfloat sourceVel_[3];

	//听者位置和速度（暂不用）
	ALfloat listenerPos_[3];
	ALfloat listenerVel_[3];
	ALfloat ListenerOri[6];

	//声音数据和声音源
	ALuint sourceData_;
	ALuint source_;

	//循环次数
	int nLoopCount_;

	//播放位置偏移
	int nPlayOffset_;
};

typedef shared_ptr<WaveSound> WaveSoundPtr;

#endif	//end of WaveSound.h