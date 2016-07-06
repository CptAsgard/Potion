#include "UniqueID.hpp"

namespace Potion
{
	UniqueID::UniqueID() : nextID( 0 )
	{
		this->freeIDs = std::stack<ID>();
	}

	ID UniqueID::GetNext()
	{
		ID newID;

		if( freeIDs.size() != 0 )
		{
			newID = freeIDs.top();
			freeIDs.pop();
		}
		else
		{
			newID = nextID;
			nextID++;
		}

		return newID;
	}

	void UniqueID::Free( ID id )
	{
		freeIDs.push( id );
	}
}