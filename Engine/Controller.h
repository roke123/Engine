#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

class Controller
{
public:
	//���캯��
	Controller() : isAvailable_(true)
	{
		//����
	}

	//����������
	virtual ~Controller(){}

	//������ע��Ŀ�����
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