#pragma once

namespace JZEngine
{
	namespace MessageID
	{
		enum MessageIDType
		{
			ToggleDebugInfo,
			CharacterKey,
			MouseButton,
			PlaySound
		};
	}

	class Message
	{
	public:
		Message(MessageID::MessageIDType id) : messageID(id) {};
		virtual ~Message() {};

	private:
		MessageID::MessageIDType messageID;
	};



}