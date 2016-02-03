#include "GameState.hpp"
#include "StateManager.hpp"

namespace Potion
{
	/**
	 * Init creates the window, and starts the game.
	 */
	void StateManager::Init( const std::string& title, int32_t width, int32_t height )
	{
		this->windowPtr = new Window();
		this->messageBus = new MessageBus();

		// Create the window
		windowPtr->Create( title, width, height );

		gameIsRunning = true;
	}

	/**
	 * CleanUp should be called when the game has to completely halt execution.
	 * NOTE: Will be called when the game loop exits. If you want to stop the game, call Quit().
	 */
	void StateManager::CleanUp()
	{
		for( uint8_t i = 0; i < states.size(); i++ ) {
			PopState();
		}

		// delete window
		windowPtr->Close();
	}


	/**
	 * Will clean up the current state, and push the given state to the top of the stack, and Init() it.
	 * ChangeState should be used when the state of the previous state doesn't matter anymore.
	 */
	void StateManager::ChangeState( GameState* state )
	{
		if( !states.empty() ) {
			states.back()->CleanUp();
			states.pop_back();
		}

		states.push_back( state );
		states.back()->Init( this );
	}

	/**
	 * Will pause the current state, and push the given state to the top of the stack, and Init() it.
	 * PushState should be used when you only want to temporarily halt a state, and come back to it later.
	 */
	void StateManager::PushState( GameState* state )
	{
		if( !states.empty() ) {
			states.back()->Pause();
		}

		states.push_back( state );
		states.back()->Init( this );
	}

	/**
	 * Will clean up the current state, and go back to the previous state on the stack.
	 * Use this to revert to the old state.
	 */
	void StateManager::PopState()
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
	void StateManager::HandleEvents()
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
	void StateManager::Update()
	{
		states.back()->Update( this, 0 );
	}

	/**
	 * Will let the current state draw.
	 */
	void StateManager::Draw()
	{
		// clear
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		states.back()->Draw( this );

		windowPtr->SwapBuffer();
	}

	const Window& StateManager::GetWindow() const
	{
		return *windowPtr;
	}
}