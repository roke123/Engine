#ifndef __SOUNDSYSTEM_H__
#define __SOUNDSYSTEM_H__

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
};

#endif	//end of SoundSystem.h