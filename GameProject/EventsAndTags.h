#pragma once
enum TAG : unsigned int
{
	PLAYER,
	BLOCK_CARVER,
	BLOCK,
	DUG_BLOCK,
};

enum EVENT : unsigned int
{
	MOVING,
	SELECTING,
	ENTER_SELECTION
};
enum SCENE : unsigned int
{
	FPS_TEST,
	MENU,
	SOLO,
	COOP,
	VERSUS
};
