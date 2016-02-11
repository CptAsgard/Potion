#ifndef _RENDERSYSTEM_H
#define _RENDERSYSTEM_H

#include "..\Events\MessageBus.hpp"
#include "..\World\MeshEntity.hpp"

namespace Potion
{
	struct RegisterMeshEntityMessage
	{
		MeshEntity* newObj;
	};

	class RenderSystem : MessageReceiver<RegisterMeshEntityMessage>
	{

	public:
		void HandleMessage( RegisterMeshEntityMessage msg );

		void DrawAll();

	private:


	};
}

#endif // _RENDERSYSTEM_H