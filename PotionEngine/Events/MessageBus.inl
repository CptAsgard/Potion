template<class Message>
void MessageBus::AddSubscriber( const MessageReceiverSingle<Message>& receiver )
{
	MessageReceiverBase* receiverPtr = (MessageReceiverBase*) &receiver;
	std::type_index index = std::type_index( typeid(Message) );

	if( !SubscriptionExists( index, receiverPtr ) )
		subscribers[ index ].push_back( receiverPtr );
}

template<class Message>
void MessageBus::RemoveSubscriber( const MessageReceiverSingle<Message>& receiver )
{
	MessageReceiverBase* receiverPtr = (MessageReceiverBase*) &receiver;
	std::type_index index = std::type_index( typeid(Message) );

	if( subscribers.find( index ) == subscribers.end() ) {
		printf( "REMOVING SUBSCRIBER - SUBSCRIBER DOES NOT EXIST" );
		return;
	}

	auto& list = subscribers.at( index );
	bool existed = false;

	for( auto iter = list.begin(); iter != list.end(); iter++ ) {
		if( *iter == receiverPtr ) {
			list.erase( iter );
			existed = true;
			if( list.size() == 0 )
				subscribers.erase( index );
			break;
		}
	}

	if( !existed ) {
		printf( "REMOVING SUBSCRIBER - SUBSCRIBER DOES NOT EXIST" );
		return;
	}
}

template<class Message>
void MessageBus::Send( const Message& mess )
{
	const auto listIterator = subscribers.find( std::type_index( typeid(Message) ) );
	if( listIterator != subscribers.end() ) {
		const auto& list = listIterator->second;
		if( list.size() > 0 ) {
			for( auto subscriber : list )
				static_cast<MessageReceiver<Message>*>(subscriber)->HandleMessage( mess );
		}
	}
}