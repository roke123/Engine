#ifndef __INITIALINTERFACE_H__
#define __INITIALINTERFACE_H__

#include <DrawTool.h>
#include <InputSystem.h>
#include <Default.h>

enum CHOOSEKEY
{
	CK_STARTGAME,
	CK_OPTION,
	CK_ENDGAME,
};

class InitialInterface
{
	REGISTER_CONTROLLER( InitialInputControl );
public:
	InitialInterface() : iChoose_(-1), iReadyChoose_(-1)
	{
		//Áô¿Õ
	}

	bool Init();

	void Draw( DrawTool * drawTool );

	void ShutDown();

	int GetChoose()
	{
		return iChoose_;
	}

	void Reset();

private:
	int iChoose_;
	int iReadyChoose_;

	Rect_F startGameBox_;
	Rect_F optionBox_;
	Rect_F endGameBox_;

	InputControllerPtr inputController_;
};

#endif	// end of InitialInterface.h