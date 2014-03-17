#ifndef __SOUNDSYSTEM_H__
#define __SOUNDSYSTEM_H__

#include "WaveSound.h"

#include <AL\alut.h>
#include <AL\al.h>
#include <AL\alc.h>
#include <string>
#include <list>
using namespace std;

class WaveSound;

class SoundSystem
{
public:
	//构造函数
	SoundSystem();

	//析构函数
	~SoundSystem();

	//初始化函数
	bool Init();

	//运行时函数，用于播放声音
	void Run();

	//卸载函数
	void ShutDown();

	bool CreateWaveSound( const string& sFilename, WaveSoundPtr * ppWaveSound );

	static SoundSystem * GetSoundSystem()
	{
		static SoundSystem soundSystem;

		return &soundSystem;
	}

private:
	void RegisterSound( WaveSoundPtr pWaveSound );

public:
	list< WaveSoundPtr > waveList_;
};

#endif	//end of SoundSystem.h