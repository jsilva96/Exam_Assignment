
#include "pch.h"
#include <iostream>
#include "FPSScene.h"
#include "DigDug.h"
#include "PoolManager.h"

int main()
{
	auto engine = new Minigin();

	int scale = 1;
	engine->Initialize(450 * scale, 544 * scale);
	engine->AddGameScene(new DigDug());

	engine->RunGame();

	engine->Destroy();
	delete engine;

	return 0;
}
