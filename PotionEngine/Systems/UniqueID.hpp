#pragma once

#include <stdint.h>
#include <stack>

#include "..\Utils\Defines.hpp"

namespace Potion
{
	class UniqueID
	{
	public:
		UniqueID();

		ID GetNext();
		void Free( ID id );

	private:
		std::stack<ID> freeIDs;
		ID nextID;

	};
}