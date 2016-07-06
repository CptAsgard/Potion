#ifndef _SceneGraph_H
#define _SceneGraph_H

#include <vector>
#include <algorithm>
#include <stack>

#include <functional>

#include <iostream>
#include <sstream>

#include "Renderer.hpp"
#include "UniqueID.hpp"

#include "..\Events\MessageBus.hpp"

#include "..\World\GameObject.hpp"
#include "..\World\Light.hpp"
#include "..\World\Camera.hpp"

#include "..\Rendering\Model.hpp"

#include "..\Math\MatrixStack.hpp"

// TODO
/**
 * The SceneGraph class needs a complete restructuring to adhere to the
 * Single Responsibility Principle. Things the SceneGraph currently does:
 *
 * - Facilitate creation of new game objects
 * - Facilitate finding of existing game objects
 * - Manage the lifetime and destruction of game objects
 * - Create a list of ordered draw calls
 * - Tell the Renderer what to draw
 * - Update the game objects in the graph
 * - Set the ambient color of the scene
 */
namespace Potion
{
	class GameObject;

	using DrawKey = uint32_t;

	/**
	 * The SceneGraph is an excellent base class. It can be inherited
	 * to create different behaviour for culling, or others. For example a BSPSceneGraph
	 *
	 * TODO: Some objects can be static batched
	 */
	class SceneGraph : 	MessageReceiver< LightCreatedMessage, LightDestroyedMessage,
										 CameraCreatedMessage, CameraDestroyedMessage >
	{
	public:
		SceneGraph( SceneManager* game );
		virtual ~SceneGraph() {}

		/**
		* Sets the ambient lighting color of the scene
		*/
		void SetAmbientColor( const Color &color );

		/**
		* In range [0 .. 1]
		*/
		void SetAmbientIntensity( float intensity );

		/**
		* Starts the drawing process.
		* Call when you want to start rendering all objects
		*/
		virtual void DrawAll();

		virtual void UpdateGameObjects( SceneManager* game, float deltaTime );

		/**
		 * Claims ownership of ptr. SceneGraph is responsible for managing the lifetime of the GO. 
		 * Gives the GameObject a new unique ID.
		 * Also attaches the GameObject to the root of the scene, if it doesn't have a root obj yet.
		 *
		 * @param GO The gameObject to add to this scene
		 */
		void AttachToScene( GameObject* GO );

		/**
		 * Creates a GameObject from the given model
		 * @param path The file path of the model
		 */
		virtual GameObject* CreateGameObject( const std::string& path );

		/**
		* Creates an empty GameObject
		*/
		virtual GameObject* CreateGameObject();

		/**
		 * Find a gameobject by ID
		 * @param goID the ID of the gameObject
		 * @returns GameObject pointer if it can find one, otherwise nullptr
		 */
		virtual GameObject* FindGameObject( ID goID ) const;

		/**
		* Destroy the gameobject by pointer
		*/
		virtual void DestroyGameObject( GameObject* obj );

		/**
		* Destroy the gameobject by ID
		*/
		virtual void DestroyGameObject( const ID id );

		/**
		* Returns the root of the scene
		* The root is always an empty GameObject
		*/
		virtual Transform* GetRoot();

		virtual void HandleMessage( const LightCreatedMessage& msg );
		virtual void HandleMessage( const LightDestroyedMessage& msg );

		virtual void HandleMessage( const CameraCreatedMessage& msg );
		virtual void HandleMessage( const CameraDestroyedMessage& msg );

	protected:
		/**
		*
		*/
		template <typename T>
		void SetLightUniform( Shader* shader, const char* propertyName, size_t lightIndex, const T& value );

		/**
		 * Constructs the key for proper draw call ordering
		 */
		DrawKey GenerateDrawKey( Camera * cam, Material * mat ) const;
		uint32_t CreateReadMask( uint fieldLength, uint fieldIndex ) const;
		uint32_t CreateWriteMask( uint fieldLength, uint fieldIndex ) const;

		/**
		 * Fills our draw bucket with keys of objects we want to render
		 */
		void BuildDrawBucket();

		/// Can be passed a routine to execute on each node
		void Recurse( Transform* node, MatrixStack& stack, std::function<void( Transform* )> const& routine );

		void UpdateNode( Transform * node, SceneManager* game, float deltaTime );
		void AddNodeToDrawBucket( Transform* node, Camera* cam, Matrix* worldMat );

	protected:
		SceneManager* game;

		Material mat;

		Transform root;

		std::multimap< DrawKey, RenderDataPayload, std::greater<int> > drawBucket;

		std::unordered_map<ID, GameObjectPtr> gameObjects;
		std::vector<Light*> lights;
		std::vector<Camera*> cameras;

		UniqueID uniqueID;

		Color ambientColor;

		// [0 .. 1]
		float ambientIntensity;

	};
}

#endif // _SceneGraph_H