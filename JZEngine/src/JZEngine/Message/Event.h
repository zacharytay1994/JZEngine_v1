/*	__FILE HEADER__
*	File:		Event.h
	Primary:	Yu Ching Yin
	Date:		01/07/21
	Brief:		Event class.
*/

#pragma once

#include "../Message/MessageHandler.h"
#include <string>

namespace JZEngine
{
	class SoundEvent : public Event
	{
	public:
		std::string name = "mellau__button-click-1.wav";

	};
}
