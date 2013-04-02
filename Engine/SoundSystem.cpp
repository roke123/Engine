#ifndef __SOUNDSYSTEM_H__
#define __SOUNDSYSTEM_H__

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
};

#endif	//end of SoundSystem.h