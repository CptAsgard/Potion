#pragma once
#ifndef _STATEMANAGER_H
#define _STATEMANAGER_H

#include <iostream>
#include <vector>
#include <cstdint>

#include "..\Events\MessageBus.hpp"
#include "..\Rendering\Window.hpp"

namespace Potion
{
	class GameState;

	class StateManager
	{

	public:
		void Init( const std::string& title, int32_t width, int32_t height );
		void CleanUp();

		void ChangeState( GameState *state );
		void PushState( GameState *state );
		void PopState();

		void HandleEvents();
		void Update();
		void Draw();

		bool Running() { return gameIsRunning; }
		void Quit() { gameIsRunning = false; }

		const Window& GetWindow() const;

	private:
		std::vector<GameState*> states;

		Window* windowPtr;

		MessageBus* messageBus;

		bool gameIsRunning;

	};
}
#endif // _STATEMANAGER_H