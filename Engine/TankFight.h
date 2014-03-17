#ifndef __TankFight_H__
#define __TankFight_H__

#include <Windows.h>
#include <SimpleApp.h>
#include <SwapChain2D.h>
#include <SoundSystem.h>

#include "InitialInterface.h"
#include "Map.h"

class TankFight : public SimpleApp
{
public:
	TankFight( );
	~TankFight( );

	//override
	bool Init( HINSTANCE hInstance, int width, int height,
		bool isWindow, WndProc process  );

	void Render( );

	void Run( );

	void ShutDown( );

private:
	//·ÀÖ¹¸´ÖÆ´°¿Ú
	TankFight( const TankFight& t ) { };
	TankFight operator = ( const TankFight& t ) { };

private:
	bool LoadContent()
	{
		map_.Init( swapChain_.GetDrawTool(), 800, 640 );
		SoundSystem::GetSoundSystem()->CreateWaveSound(
			"music/bgm.wav", 
			&bgm_
			);
		return initialInterface_.Init();
	}

private:
	SwapChain2D swapChain_;

	InitialInterface initialInterface_;
	Map map_;

	WaveSoundPtr bgm_;
};

#endif	//end of TankFight.h