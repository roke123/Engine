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
	//���캯��
	SoundSystem();

	//��������
	~SoundSystem();

	//��ʼ������
	bool Init();

	//����ʱ���������ڲ�������
	void Run();

	//ж�غ���
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