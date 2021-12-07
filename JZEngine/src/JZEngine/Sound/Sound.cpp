/*	__FILE HEADER__
*	File:		Sound.cpp
    Primary:	Deon Khong
    Date:		01/07/21
    Brief:		Sound class.
*/

#include "PCH.h"
#include "Sound.h"
#include "../Message/MessageHandler.h"
#include "../DebugTools/Log.h"
#include "../JZGL/JZ_GL.h"

namespace JZEngine
{
    SoundSystem::SoundSystem() : mutebool{ false }, fmodsystem{ nullptr }, sfxchannelgrp{ nullptr }, bgmchannelgrp{ nullptr }
    { }
    SoundSystem::~SoundSystem()
    {
        for (auto i : sound_cont)
        {
            i.second->release();
        }
        //fmodsystem->release();
    }
    /**
     * \Brief Initialises the sound system with a default channel group (called "main") that controls all the sounds under
        the system.
     *  The max number of channels is set to 36
     */
    void SoundSystem::Init()
    {
        mastervolume = 0.33f;
        mainvolume = 0.2f;
        bgmvolume = 0.2f;

        FMOD_RESULT result = FMOD_OK;
        result = FMOD::System_Create(&fmodsystem);
       
        if (result != FMOD_OK)
        {
            std::cout << "create system failed\n";
            exit(-1);
        }

        int driverCount = 0;
        fmodsystem->getNumDrivers(&driverCount);

        if (driverCount == 0)
        {
            std::cout << "no driver\n";
            exit(-1);
        }

        // Initialize with 36 Channels
       
        fmodsystem->init(MAX_CHANNELS, FMOD_INIT_NORMAL, nullptr);
        fmodsystem->createChannelGroup(0, &sfxchannelgrp);
        fmodsystem->createChannelGroup(0, &bgmchannelgrp);
        channelgroup_cont["sfx"] = sfxchannelgrp;
        channelgroup_cont["bgm"] = bgmchannelgrp;
        channel_cont.resize(MAX_CHANNELS);
    
        setMasterVolume(mastervolume);
    }
    // To be called every loop
    void SoundSystem::Update(float dt)
    {
        UNREFERENCED_PARAMETER(dt);
        if ( GLFW_Instance::focused_ && !focused_ )
        {
            focused_ = GLFW_Instance::focused_;
            setPauseSoundSystem ( false );
        }
        if ( !GLFW_Instance::focused_ && focused_ )
        {
            focused_ = GLFW_Instance::focused_;
            setPauseSoundSystem ( true );
        }
        fmodsystem->update ();
    }
    /**
     * Creates a sound and stores it in the container.
     * 
     * \param name      name of the sound
     * \param pFile     filepath of the sound file
     */
    void SoundSystem::createSound(std::string const& name, const char* pFile)
    {
        FMOD::Sound* temp;
        FMOD_RESULT result;
        result=fmodsystem->createSound(pFile, FMOD_DEFAULT, 0, &temp);
        if (result != FMOD_OK)
        {
            std::cout << "create sound failed\n";
            exit(-1);
        }
        sound_cont.insert(std::pair<std::string, FMOD::Sound*>(name, temp));
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
    int SoundSystem::playSound(std::string const& name, bool bLoop, float volume)
    {
        UNREFERENCED_PARAMETER ( volume );
        if (!bLoop)
            sound_cont[name]->setMode(FMOD_LOOP_OFF);
        else
        {
            sound_cont[name]->setMode(FMOD_LOOP_NORMAL);
            sound_cont[name]->setLoopCount(1000);
        }

        FMOD::Channel* fchannel;
        FMOD_RESULT result = FMOD_OK;
        if (name == "bgm")
        {
            result = fmodsystem->playSound(sound_cont[name], bgmchannelgrp, false, &fchannel);
            Log::Info("Sound", "bgm channelgroup");
        }
        else
        {
            result = fmodsystem->playSound(sound_cont[name], sfxchannelgrp, false, &fchannel);
            Log::Info("Sound", "main channelgroup");
        }

        if (result != FMOD_OK)
        {
            std::cout << "play sound failed\n";
            exit(-1);
        }
        for (int i{ 0 }; i < MAX_CHANNELS; i++)
        {
          
            bool playing;
            channel_cont[i]->isPlaying(&playing);
            if (playing == false)
            {
                channel_cont[i]=fchannel;
                return i;
            }
        }
        return 0;
    }


    /**
     * Stops a sound specified by id.
     *
     * \param id
     */
    void SoundSystem::stopSound(int id)
    {
        channel_cont[id]->stop();
    }
    /**
     * Pause a sound specified by id.
     *
     * \param id
     */
    void SoundSystem::setpauseSound(int id, bool pausestate)
    {
        channel_cont[id]->setPaused(pausestate);
    }

    /**
    * Releases pause/unpause soundsystem
    *
    * \param pausestate
    */
    void SoundSystem::setPauseSoundSystem(bool pausestate)
    {
        for (auto& channelgrp : channelgroup_cont)
        {
            channelgrp.second->setPaused(pausestate);
        }
    }


    /**
     * Releases a sound specified by name.
     * 
     * \param name
     */
    void SoundSystem::releaseSound(std::string const& name)
    {
        sound_cont[name]->release();
    }


    /**
     * Set the volume of the main channel group.
     *
     * \param volume ... Range [0.0f - 1.0f]
     */
    void SoundSystem::setEffectsChannelGroupVolume(float volume)
    {
        Log::Info("Sound", "setting effects vol");
        mainvolume = volume;
        sfxchannelgrp->setVolume(mainvolume *mastervolume);
    }
    /**
     * Set the volume of the BGM channel group.
     *
     * \param volume ... Range [0.0f - 1.0f]
     */
    void SoundSystem::setBGMChannelGroupVolume(float volume)
    {
        Log::Info("Sound", "setting bgm vol");
        bgmvolume = volume;
        bgmchannelgrp->setVolume(bgmvolume * mastervolume);
    }

    /**
     * Set the volume of the master volume.
     *
     * \param volume ... Range [0.0f - 1.0f]
     */
    void SoundSystem::setMasterVolume(float volume)
    {
        Log::Info("Sound", "setting master vol {} ", volume);
        mastervolume = volume;
        Log::Info("Sound", "setting bgmchannelgrp vol {} ", bgmvolume * mastervolume);
        bgmchannelgrp->setVolume(bgmvolume * mastervolume);
        sfxchannelgrp->setVolume(mainvolume * mastervolume);
    }

    /**
     * Create a new channel group which will be stored in the Channel Group container.
     * Channels can be added to Channel Groups using setChannelGroup(..) function
     *
     * \param name
     */
    void SoundSystem::createChannelGroup(std::string const& name)
    {
        FMOD::ChannelGroup* newchannelgroup;
        fmodsystem->createChannelGroup(name.c_str(), &newchannelgroup);
        channelgroup_cont[name] = newchannelgroup;
    }
    /**
     * Sets a channel as a part of a channelgroup.
     * It is necessary to get the ID of channel that is currently playing(can be paused)
     * before setting as channels are gone when the sound ends.
     *
     * \param channelgroupname
     * \param fchannel
     */
    void SoundSystem::setChannelGroup(std::string const& channelgroupname, int channelid)
    {
        channel_cont[channelid]->setChannelGroup(channelgroup_cont[channelgroupname]);
    }
    /**
     * Stops the sound of a channel group specified by name.
     *
     * \param name  the name of the channel group
     */
    void SoundSystem::stopChannelGroup(std::string const& name)
    {
        channelgroup_cont[name]->stop();
    }
    /**
     * Set the volume of a channel group.
     *
     * \param x
     * \param name
     */
    void SoundSystem::setChannelGroupVolume(float x, std::string const& name)
    {
        channelgroup_cont[name]->setVolume(x);
    }

    // Mute toggle for sound system
    void SoundSystem::toggleMute()
    {
        mutebool = !mutebool;
        sfxchannelgrp->setMute(mutebool);
        bgmchannelgrp->setMute(mutebool);
    }

    void SoundSystem::RecursivelyLoadSounds(const std::string& folder, FolderData& folderData)
    {
        std::string path;
        std::string sound_name;
        std::unordered_map<std::string, bool> check;
        //Log::Info("Resources", "\n Reading textures from {}:", folder);
        for (const auto& file : std::filesystem::directory_iterator(folder))
        {
            if (std::filesystem::is_directory(file.path()))
            {
                folderData.folders_.emplace_back();
                folderData.folders_.back().path_ = file.path().string();
                folderData.folders_.back().name_ = file.path().filename().string();
                //texture_folders_[folderData.folders_.back().name_] = &folderData.files_;
                std::cout << file.path().string() << std::endl;
                RecursivelyLoadSounds(file.path().string(), folderData.folders_.back());
            }
            else
            {
                sound_name = file.path().filename().string();
                sound_name = sound_name.substr(0, sound_name.find_last_of('.'));
                folderData.files_.emplace_back(sound_name);
                sound_folders_[folderData.name_].emplace_back(sound_name);
                std::cout << sound_name << std::endl;
                std::cout << file.path().string() << std::endl;
                createSound(sound_name, file.path().string().c_str());
                // check if texture not already loaded
                /*if (umap_texture2ds_.find(texture_name) == umap_texture2ds_.end())
                {
                    texture2ds_.emplace_back(static_cast<int>(texture2ds_.size()));
                    texture2ds_.back().texture2d_.Texture2DLoad(file.path().string());
                    umap_texture2ds_[texture_name] = texture2ds_.back().id_;
                    Log::Info("Resources", "- Read [{}].", file.path().string());
                }
                check[texture_name] = true;*/
            }
        }
    }

    void SoundSystem::LoadAllSoundsInFolder(const std::string& soundFolder)
    {
        if (!std::filesystem::is_directory(soundFolder))
        {
            std::filesystem::create_directory(soundFolder);
        }

        sound_folder_data_ = FolderData();
        sound_folders_ = std::unordered_map<std::string, std::vector<std::string>>();
        sound_folder_data_.path_ = "All Sounds";
        sound_folder_data_.name_ = "Sounds";
        RecursivelyLoadSounds(soundFolder, sound_folder_data_);
    }

}