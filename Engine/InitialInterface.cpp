#include "InitialInterface.h"
#include "InitialInputControl.h"

bool InitialInterface::Init()
{
	startGameBox_.x0 = 300.0f;
	startGameBox_.y0 = 400.0f;
	startGameBox_.x1 = 500.0f;
	startGameBox_.y1 = 450.0f;

	optionBox_.x0 = 300.0f;
	optionBox_.y0 = 450.0f;
	optionBox_.x1 = 500.0f;
	optionBox_.y1 = 500.0f;

	endGameBox_.x0 = 300.0f;
	endGameBox_.y0 = 500.0f;
	endGameBox_.x1 = 500.0f;
	endGameBox_.y1 = 550.0f;

	inputController_.reset( new InitialInputControl );
	RegisterInputControl( inputController_ );

	return true;
}

void InitialInterface::Draw( DrawTool * drawTool )
{
	drawTool->SetTextFormat( L"Chinese", 40.0f, L"zh-cn" ); 
	Color_F red = { 1.0f, 0.0f, 0.0f, 1.0f };
	Color_F white = { 1.0f, 1.0f, 1.0f, 1.0f };

	Rect_F title = { 250.0f, 200.0f, 600.0f, 300.0f };

	drawTool->DrawString( L"TANK   FIGHT", title, red );

	drawTool->SetTextFormat( L"Chinese", 20.0f, L"zh-cn" ); 

	if( iReadyChoose_ == CK_STARTGAME )
		drawTool->DrawString( L"STARTGAME", startGameBox_, red );
	else
		drawTool->DrawString( L"STARTGAME", startGameBox_, white );

	if( iReadyChoose_ == CK_OPTION )
		drawTool->DrawString( L"OPTION", optionBox_, red );
	else
		drawTool->DrawString( L"OPTION", optionBox_, white );

	if( iReadyChoose_ == CK_ENDGAME )
		drawTool->DrawString( L"ENDGAME", endGameBox_, red );
	else
		drawTool->DrawString( L"ENDGAME", endGameBox_, white );	
}

void InitialInterface::ShutDown()
{
	if( inputController_ != NULL )
		UnregisterInputControl( inputController_ );

	inputController_ = NULL;
}

void InitialInterface::Reset()
{
	inputController_.reset( new InitialInputControl );
	RegisterInputControl( inputController_ );
	iChoose_ = -1;
}