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
	//��������
	
	~WaveSound();

	void SetVolume( ALfloat dwVolume );

	float GetVolume();

	//ȡ��
	void GetState( int * dwFlag );

	int Play( int nLoopCount = 1, int nPlayOffset = 0 );

	//bFlag = trueֹͣ��false�ָ�
	int Pause( bool bFlag = true );

	//SOUND_STOP_RELEASEΪ������ɵ�ǰһ��ѭ����ֹͣ
	//SOUND_STOP_IMMEDIATEΪ����ֹͣ����
	void Stop( int nFlag = SOUND_STOP_IMMEDIATE );

private:
	//���캯��
	WaveSound();

	//��ʼ������,�����ļ�
	bool Init( const string& wsFilename );

	//ж�ص�ǰ����
	void ShutDown();

private:
	//����Դλ�ú��ٶȣ��ݲ��ã�
	ALfloat sourcePos_[3];
	ALfloat sourceVel_[3];

	//����λ�ú��ٶȣ��ݲ��ã�
	ALfloat listenerPos_[3];
	ALfloat listenerVel_[3];
	ALfloat ListenerOri[6];

	//�������ݺ�����Դ
	ALuint sourceData_;
	ALuint source_;

	//ѭ������
	int nLoopCount_;

	//����λ��ƫ��
	int nPlayOffset_;
};

typedef shared_ptr<WaveSound> WaveSoundPtr;

#endif	//end of WaveSound.h