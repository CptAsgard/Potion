#include "MessageBus.hpp"

namespace Potion
{
	bool MessageBus::SubscriptionExists( std::type_index id, MessageReceiverBase* receiver )
	{
		const auto listIterator = subscribers.find( id );

		if( listIterator == subscribers.end() )
			return false;

		const auto& list = listIterator->second;
		bool existed = false;

		for( const auto subscriber : list ) {
			if( subscriber == receiver ) {
				existed = true;
				break;
			}
		}
		return existed;
	}
}