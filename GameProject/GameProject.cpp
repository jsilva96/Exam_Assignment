
#include "pch.h"
#include <iostream>
#include "FPSScene.h"
#include "DigDug.h"
#include "PoolManager.h"

int main()
{
	auto engine = new Minigin();
	engine->Initialize(225, 272);
	engine->AddGameScene(new DigDug());

	engine->RunGame();

	engine->Destroy();
	delete engine;

	return 0;
}
