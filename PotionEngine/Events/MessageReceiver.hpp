#pragma once
#ifndef _MESSAGERECEIVER_H
#define _MESSAGERECEIVER_H

#include <functional>
#include <vector>

namespace Potion
{
	class MessageBus;

	template<class... MessageTypes>
	class MessageReceiver;

	template <class... MessageTypes>
	void Subscribe( MessageBus&, MessageReceiver<MessageTypes...>&, bool = true );

	class MessageReceiverBase {};

	template<class MessageType>
	class MessageReceiverSingle : public MessageReceiverBase
	{
	public:
		virtual void HandleMessage( const MessageType& message ) = 0;
	};

	template<class... MessageTypes>
	class MessageReceiver : public MessageReceiverSingle<MessageTypes>...
	{
	public:
		virtual ~MessageReceiver()
		{
			for( auto desubscriber : desubscribers ) {
				desubscriber();
			}
		}

	private:
		std::vector<std::function<void()>> desubscribers;

		template <class... Types>
		friend void Subscribe( MessageBus& bus, MessageReceiver<Types...>&, bool );

	};
}
#endif // _MESSAGERECEIVER_H