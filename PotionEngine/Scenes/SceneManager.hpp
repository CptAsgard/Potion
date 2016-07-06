#pragma once

#include <iostream>
#include <vector>
#include <cstdint>

#include "..\Events\MessageBus.hpp"

#include "..\Rendering\Window.hpp"

#include "..\Systems\SceneGraph.hpp"

namespace Potion
{
	class Scene;

	class SceneManager
	{

	public:
		void Initialize( const std::string& title, int32_t width, int32_t height );
		void CleanUp();

		void ChangeState( Scene *state );
		void PushState( Scene *state );
		void PopState();

		void HandleEvents();
		void Update();
		void Draw();

		bool Running() { return gameIsRunning; }
		void Quit() { gameIsRunning = false; }

		Window* GetWindow();

		SceneGraph* GetSceneGraph();

	private:
		std::vector<Scene*> states;

		Window* windowPtr;

		MessageBus* messageBus;

		SceneGraph* sceneGraph;

		bool gameIsRunning;

		float elapsedTime;

	};
}