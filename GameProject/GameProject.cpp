
#include "pch.h"
#include <iostream>
#include "FPSScene.h"
#include "DigDug.h"
#include "PoolManager.h"

int main()
{
	auto engine = new Minigin();

	int scale = 2;
	engine->Initialize(225 * scale, 272 * scale);
	engine->AddGameScene(new DigDug());

	engine->RunGame();

	engine->Destroy();
	delete engine;

	return 0;
}
