/*	__FILE HEADER__
*	File:		Sound.cpp
	Primary:	Deon Khong
	Date:		01/07/21
	Brief:		Sound class.
*/

#include "PCH.h"
#include "Sound.h"
#include "../Message/MessageHandler.h"

namespace JZEngine
{
	SoundSystem::SoundSystem () : mutebool{ false } , fmodsystem{ nullptr } , mainchannelgrp{ nullptr }
	{}
	SoundSystem::~SoundSystem ()
	{
		for( auto i : sound_cont )
		{
			i.second->release ();
		}
		//fmodsystem->release();
	}
	/**
	 * \Brief Initialises the sound system with a default channel group (called "main") that controls all the sounds under
		the system.
	 *  The max number of channels is set to 36
	 */
	void SoundSystem::Init ()
	{
		FMOD_RESULT result = FMOD_OK;
		result = FMOD::System_Create ( &fmodsystem );

		if( result != FMOD_OK )
		{
			std::cout << "create system failed\n";
			exit ( -1 );
		}

		int driverCount = 0;
		fmodsystem->getNumDrivers ( &driverCount );

		if( driverCount == 0 )
		{
			std::cout << "no driver\n";
			exit ( -1 );
		}

		// Initialize with 36 Channels

		fmodsystem->init ( MAX_CHANNELS , FMOD_INIT_NORMAL , nullptr );
		fmodsystem->createChannelGroup ( 0 , &mainchannelgrp );
		channelgroup_cont[ "main" ] = mainchannelgrp;
		channel_cont.resize ( MAX_CHANNELS );

	}
	// To be called every loop
	void SoundSystem::Update ( float dt )
	{
		fmodsystem->update ();
	}
	/**
	 * Creates a sound and stores it in the container.
	 *
	 * \param name      name of the sound
	 * \param pFile     filepath of the sound file
	 */
	void SoundSystem::createSound ( std::string const& name , const char* pFile )
	{
		FMOD::Sound* temp;
		FMOD_RESULT result;
		result = fmodsystem->createSound ( pFile , FMOD_DEFAULT , 0 , &temp );
		if( result != FMOD_OK )
		{
			std::cout << "create sound failed\n";
			exit ( -1 );
		}
		sound_cont.insert ( std::pair<std::string , FMOD::Sound*> ( name , temp ) );
	}
	/** \Brief Plays a sound and saves the channel used to channel container
	 *   All sounds created are stored in a channelgroup called
	 * .
	 *
	 * \param name      The name of the sound created
	 * \param bLoop     True if loop of the sound is necessary
	 * \param volume    Sets the volume of the channel of the sound
	 *                  Range ( 0.0f , 1.0f )
	 * \return          The ID of the channel of the sound
	 */
	int SoundSystem::playSound ( std::string const& name , bool bLoop , float volume )
	{
		if( !bLoop )
			sound_cont[ name ]->setMode ( FMOD_LOOP_OFF );
		else
		{
			sound_cont[ name ]->setMode ( FMOD_LOOP_NORMAL );
			sound_cont[ name ]->setLoopCount ( 1000 );
		}

		FMOD::Channel* fchannel;
		FMOD_RESULT result = FMOD_OK;
		result = fmodsystem->playSound ( sound_cont[ name ] , mainchannelgrp , false , &fchannel );
		fchannel->setVolume ( volume );

		if( result != FMOD_OK )
		{
			std::cout << "play sound failed\n";
			exit ( -1 );
		}
		for( int i{ 0 }; i < MAX_CHANNELS; i++ )
		{
			bool playing;
			channel_cont[ i ]->isPlaying ( &playing );
			if( playing == false )
			{
				channel_cont[ i ] = fchannel;
				return i;
			}
		}
		return 0;
	}

	void SoundSystem::playSound ( SoundEvent* msg )
	{
		//this just calls the normal playSound function
		playSound ( msg->name , false , 0.1f );
	}

	/**
	 * Releases a sound specified by name.
	 *
	 * \param name
	 */
	void SoundSystem::releaseSound ( std::string const& name )
	{
		sound_cont[ name ]->release ();
	}
	/**
	 * Create a new channel group which will be stored in the Channel Group container.
	 * Channels can be added to Channel Groups using setChannelGroup(..) function
	 *
	 * \param name
	 */
	void SoundSystem::createChannelGroup ( std::string const& name )
	{
		FMOD::ChannelGroup* newchannelgroup;
		fmodsystem->createChannelGroup ( name.c_str () , &newchannelgroup );
		channelgroup_cont[ name ] = newchannelgroup;
	}
	/**
	 * Sets a channel as a part of a channelgroup.
	 * It is necessary to get the ID of channel that is currently playing(can be paused)
	 * before setting as channels are gone when the sound ends.
	 *
	 * \param channelgroupname
	 * \param fchannel
	 */
	void SoundSystem::setChannelGroup ( std::string const& channelgroupname , int channelid )
	{
		channel_cont[ channelid ]->setChannelGroup ( channelgroup_cont[ channelgroupname ] );
	}
	/**
	 * Stops the sound of a channel group specified by name.
	 *
	 * \param name  the name of the channel group
	 */
	void SoundSystem::stopChannelGroup ( std::string const& name )
	{
		channelgroup_cont[ name ]->stop ();
	}
	/**
	 * Set the volume of a channel group.
	 *
	 * \param x
	 * \param name
	 */
	void SoundSystem::setChannelGroupVolume ( float x , std::string const& name )
	{
		channelgroup_cont[ name ]->setVolume ( x );
	}

	// Mute toggle for sound system
	void SoundSystem::toggleMute ()
	{
		mutebool = !mutebool;
		mainchannelgrp->setMute ( mutebool );
	}



}