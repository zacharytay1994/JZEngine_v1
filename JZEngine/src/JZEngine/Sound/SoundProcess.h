/*	__FILE HEADER__
*	File:		
	Primary:	
	Date:		
	Brief:		ECS system to run sounds system.
*/

#pragma once

#include "../ECS/ECS.h"
#include "Sound.h"

namespace JZEngine
{
	struct Sound
	{
		int sound_id_{ 0 };
	};

	// sound system using ecs
	struct SoundProcess : public ECS::System
	{
		SoundSystem sound_system_;

		SoundProcess ();

		virtual void FrameBegin ( const float& dt ) override;

		virtual void Update ( const float& dt ) override;
	};
}