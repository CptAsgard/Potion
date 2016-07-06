#include "Scene.hpp"
#include "SceneManager.hpp"

namespace Potion
{
	/**
	 * Initialize creates the window, and starts the game.
	 */
	void SceneManager::Initialize( const std::string& title, int32_t width, int32_t height )
	{
		this->windowPtr = new Window();
		this->messageBus = new MessageBus();

		// Create the window
		windowPtr->Create( title, width, height );

		// Can't create the graphical scene graph if glfw isn't initialized yet!
		this->sceneGraph = new SceneGraph( this );

		gameIsRunning = true;
	}

	/**
	 * CleanUp should be called when the game has to completely halt execution.
	 * NOTE: Will be called when the game loop exits. If you want to stop the game, call Quit().
	 */
	void SceneManager::CleanUp()
	{
		for( uint8_t i = 0; i < states.size(); i++ ) {
			PopState();
		}

		// delete window
		windowPtr->Close();
	}


	/**
	 * Will clean up the current state, and push the given state to the top of the stack, and Initialize() it.
	 * ChangeState should be used when the state of the previous state doesn't matter anymore.
	 */
	void SceneManager::ChangeState( Scene* state )
	{
		if( !states.empty() ) {
			states.back()->CleanUp();
			states.pop_back();
		}

		states.push_back( state );
		states.back()->Initialize( this );
	}

	/**
	 * Will pause the current state, and push the given state to the top of the stack, and Initialize() it.
	 * PushState should be used when you only want to temporarily halt a state, and come back to it later.
	 */
	void SceneManager::PushState( Scene* state )
	{
		if( !states.empty() ) {
			states.back()->Pause();
		}

		states.push_back( state );
		states.back()->Initialize( this );
	}

	/**
	 * Will clean up the current state, and go back to the previous state on the stack.
	 * Use this to revert to the old state.
	 */
	void SceneManager::PopState()
	{
		if( !states.empty() ) {
			states.back()->CleanUp();
			states.pop_back();
		}

		if( !states.empty() ) {
			states.back()->Resume();
		}
	}


	/**
	 * Will let the current state handle the events.
	 */
	void SceneManager::HandleEvents()
	{
		windowPtr->PollEvents();

		states.back()->HandleEvents();

		// Close window requested
		if( windowPtr->IsClosing() ) {
			Quit();
		}
	}

	/**
	 * Will let the current state update.
	 */
	void SceneManager::Update()
	{
		float currentTime = glfwGetTime();
		float deltaTime = currentTime - elapsedTime;
		elapsedTime = currentTime;

		states.back()->Update( this, deltaTime );

		windowPtr->UpdateKeyHolding();
	}

	/**
	 * Will let the current state draw.
	 */
	void SceneManager::Draw()
	{
		states.back()->Draw( this );

		windowPtr->SwapBuffer();
	}

	Window* SceneManager::GetWindow()
	{
		return windowPtr;
	}

	SceneGraph * SceneManager::GetSceneGraph()
	{
		return sceneGraph;
	}
}