/*	__FILE HEADER__
*	File:		DataContainer.h
	Primary:	Zachary Tay
	Date:		01/07/21
	Brief:		Custom Data.
*/

#pragma once

namespace JZEngine
{
	struct CustomDataContainer
	{
		static constexpr int CUSTOM_DATA_SIZE = 128;

		bool initialized { false };
		char data[ CUSTOM_DATA_SIZE ] { 0 };
	};
}