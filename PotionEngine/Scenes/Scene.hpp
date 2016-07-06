#pragma once

#include "SceneManager.hpp"

namespace Potion
{
	/*
	* This class is the abstract base class for all scenes.
	* By inheriting this class when creating a new scene ( e.g. IntroScene, MenuScene, PlayScene )
	* you will be able to push these onto the SceneManager stack.
	*/
	class Scene
	{

	public:
		virtual void Initialize( SceneManager *game ) = 0;
		virtual void CleanUp() = 0;

		virtual void Pause() = 0;
		virtual void Resume() = 0;

		virtual void HandleEvents() = 0;
		virtual void Update( SceneManager *game, float deltaTime ) = 0;
		virtual void Draw( SceneManager *game ) = 0;

		/**
		 * Change the state to the next given state
		 * @param	game	pointer to the state manager
		 * @param	state	pointer to the next state
		 */
		void ChangeState( SceneManager *game, Scene *state )
		{
			game->ChangeState( state );
		}

	protected:
		Scene() {}

	};
}








