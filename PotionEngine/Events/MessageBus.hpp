#pragma once
#ifndef _MESSAGEBUS_H
#define _MESSAGEBUS_H

#include "MessageReceiver.hpp"

#include <vector>
#include <functional>
#include <unordered_map>
#include <typeindex>

/**
 * @author	Zagabar
 */
namespace Potion
{
	class MessageBus
	{

	public:
		template<class Message>
		void AddSubscriber( const MessageReceiverSingle<Message>& receiver );

		template<class Message>
		void RemoveSubscriber( const MessageReceiverSingle<Message>& receiver );

		template<class Message>
		void Send( const Message& mess );

	private:
		bool SubscriptionExists( std::type_index id, MessageReceiverBase* receiver );

		std::unordered_map<std::type_index, std::vector<MessageReceiverBase*>> subscribers;

	};

	template<class MessageType>
	void SubscribeToType( MessageBus& bus, MessageReceiverSingle<MessageType>& receiver, std::vector<std::function<void()>>& desubscribers, bool unsubscribe )
	{
		bus.AddSubscriber<MessageType>( receiver );

		if( unsubscribe )
			desubscribers.push_back( [&]() { bus.RemoveSubscriber<MessageType>( receiver ); } );
	}

	template<class... MessageTypes>
	void Subscribe( MessageBus& bus, MessageReceiver<MessageTypes...>& receiver, bool unsubscribe )
	{
		std::vector<std::function<void()>> desubscribers;
		int _[] = { (SubscribeToType<MessageTypes>( bus, receiver, desubscribers, unsubscribe ), 0)... };
		(void) _;
		receiver.desubscribers = desubscribers;
	}

#include "MessageBus.inl"
}

#endif // _MESSAGEBUS_H