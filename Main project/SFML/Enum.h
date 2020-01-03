#pragma once

#define SPEED 800
#define GRAVITY 9.81
#define GRAVITYFACTOR 7

namespace e_Enum
{
	//Liste de scene
	enum e_Scene
	{
		CHARGEMENT,
		INTRO,
		MENU,
		JEU,
		OPTIONS,
		COMMANDES,
		CREDITS,
		LEVELSELECTOR,
		CHOOSELEVELEDITOR,
		OPENLEVELEDITOR,
		LEVELEDITOR,
		SIZEEDITOR,
		SAVEEDITOR,
		PLAYERSELECTOR,
		LEVELFINISHED
	};

	enum e_Collects
	{
		ROCKET = 1,
		SHOCKWAVE,
		OILFLAKE,
		LEVITATION,
		SWAP,
		BUMPER
	};
}