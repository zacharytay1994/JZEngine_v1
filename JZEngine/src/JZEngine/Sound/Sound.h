/*	__FILE HEADER__
*	File:		Sound.h
	Primary:	Deon Khong
	Date:		01/07/21
	Brief:		Sound class.
*/

#pragma once

#include "fmod.hpp"
#include "fmod_errors.h"

#include "../BuildDefinitions.h"
#include "../Message/Event.h"
#include "../GlobalSystems.h"

constexpr int MAX_CHANNELS = 36;
namespace JZEngine
{

	class JZENGINE_API SoundSystem : public GlobalSystem
	{
	public:
		SoundSystem();
		~SoundSystem();

		virtual void Init() override;
		virtual void Update(float dt);

		void createSound(std::string const &name, const char *pFile);
		int playSound(std::string const &name, bool bLoop = false, float volume = 1.0f);
		void playSound(SoundEvent *);
		void stopSound(int id);
		void releaseSound(std::string const &name);

		void createChannelGroup(std::string const &name);
		void setChannelGroup(std::string const &channelgroupname, int channelid);
		void stopChannelGroup(std::string const &name);
		void setChannelGroupVolume(float x, std::string const &name);

		void setMasterVolume(float volume);
		void toggleMute();

	private:
		float mastervolume;
		bool mutebool;
		FMOD::System *fmodsystem;
		FMOD::ChannelGroup *mainchannelgrp;
		std::vector<FMOD::Channel *> channel_cont;
		std::map<std::string, FMOD::ChannelGroup *> channelgroup_cont;
		std::map<std::string, FMOD::Sound *> sound_cont;
	};

}