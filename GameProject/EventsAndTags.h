#pragma once
enum TAG : unsigned int
{
	PLAYER,
	BLOCK_CARVER,
	BLOCK,
	DUG_BLOCK,
	POOKA,
	FYGAR
};

enum EVENT : unsigned int
{
	MOVING,
	SELECTING,
	ENTER_SELECTION,
	HOOK
};
enum SCENE : unsigned int
{
	FPS_TEST,
	MENU,
	DIG_DUG
};