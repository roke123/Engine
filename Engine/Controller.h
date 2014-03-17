#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

class Controller
{
public:
	//构造函数
	Controller() : isAvailable_(true)
	{
		//留空
	}

	//虚析构函数
	virtual ~Controller(){}

	//放弃已注册的控制器
	void QuitControl()
	{
		isAvailable_ = false;
	}

	bool IsAvailable()
	{
		return isAvailable_;
	}

	virtual void SetTarget( void * target ) = 0;

	virtual void * GetTarget() = 0;

protected:
	bool isAvailable_;
};

#endif	// end of Controller.h