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

		void stopSound(int id);
		void releaseSound(std::string const &name);

		void setEffectsChannelGroupVolume(float vol);
		void setBGMChannelGroupVolume(float volume);

		void createChannelGroup(std::string const &name);
		void setChannelGroup(std::string const &channelgroupname, int channelid);
		void stopChannelGroup(std::string const &name);
		void setChannelGroupVolume(float vol, std::string const& name);

		//specific sound
		void setpauseSound(int id, bool pausestate);

		//soundsystem
		void setPauseSoundSystem(bool pausestate);

		void setMasterVolume(float volume);
		void toggleMute();

		struct FolderData
		{
			std::string					path_;
			std::string					name_;
			std::vector<std::string>	files_;
			std::vector<FolderData>		folders_;
		};
		FolderData sound_folder_data_;
		std::unordered_map<std::string, std::vector<std::string>> sound_folders_;
		void RecursivelyLoadSounds(const std::string& folder, FolderData& folderData);
		void LoadAllSoundsInFolder(const std::string& soundFolder);

		std::map<std::string, FMOD::Sound*> sound_cont;
	private:
		float mastervolume;
		float mainvolume;
		float bgmvolume;

		bool mutebool;
		FMOD::System *fmodsystem;
		FMOD::ChannelGroup * sfxchannelgrp;
		FMOD::ChannelGroup * bgmchannelgrp;
		std::vector<FMOD::Channel *> channel_cont;
		std::map<std::string, FMOD::ChannelGroup *> channelgroup_cont;
	};

}