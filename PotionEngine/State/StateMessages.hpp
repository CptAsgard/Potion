#pragma once
#ifndef _STATEMESSAGES_H
#define _STATEMESSAGES_H

#include "StateManager.hpp"

namespace Potion
{
	class StateManager;

	struct FrameMessage
	{
		float deltaTime;
		StateManager* manager;
	};
}

#endif _STATEMESSAGES_H