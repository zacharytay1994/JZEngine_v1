#pragma once

#include <JZEngine.h>
#include <utility>
#include <string>

bool clicked_{ false };
bool roll_{ false };
int current_scene_{ 0 };
bool from_main_menu { false };

std::vector < std::pair<std::string, bool>> final_cut_scenes_ =
{
	{"CreditScene_Image04", true },
	{"CreditScene_Image03", true },
	{"CreditScene_Image02", true },
	{"CreditScene_Image01", true },
	{"CreditScene_FullCreditsRoll", true }
};

void ResetScene()
{
	for ( auto& scene : final_cut_scenes_ )
		scene.second = true;
}

bool RotateScene( std::string SceneName, float dt )
{
	float& rotation = Scene().GetComponent<JZEngine::Transform>( SceneName )->rotation_;
	return ( rotation += 180.0f * dt ) > 180.0f;
}

void DrawScene()
{
	for ( std::pair<std::string, bool>& scene : final_cut_scenes_ )
	{
		Scene().EntityFlagActive( scene.first, scene.second );
	}
}

void FinalCutSceneInit()
{
	if ( !from_main_menu )
	{
		clicked_ = false;
		roll_ = false;
		current_scene_ = 0;
		ResetScene ();
	}
	else
	{
		roll_ = true;
		current_scene_ = 4;
		for ( int i = 0; i < 4; ++i )
		{
			final_cut_scenes_[ i ].second = false;
		}
	}
}

void FinalCutSceneUpdate( float dt )
{
	if ( !roll_ )
	{
		if ( current_scene_ < final_cut_scenes_.size() - 1 )
		{
			if ( !clicked_ )
			{
				if ( JZEngine::MouseEvent* e = Scene().GetComponent<JZEngine::MouseEvent>( final_cut_scenes_[current_scene_].first ) )
				{
					if ( e->on_released_ )
					{
						clicked_ = true;
					}
				}
			}
			else
			{
				if ( RotateScene( final_cut_scenes_[current_scene_].first, dt ) )
				{
					final_cut_scenes_[current_scene_].second = false;
					++current_scene_;
					clicked_ = false;
				}
			}
		}
		else if ( current_scene_ == ( final_cut_scenes_.size() - 1 ) )
		{
			current_scene_ = final_cut_scenes_.size() - 1;
			roll_ = true;
		}
	}
	else
	{
		float& position = Scene().GetComponent<JZEngine::Transform>( final_cut_scenes_[current_scene_].first )->position_.y;
		if ( position < 2500.0f )
			position += 50.0f * dt;
		else
		{
			position = 2500.0f;
			Scene ().ChangeScene ( "MainMenu" );
		}
			
	}
	DrawScene();
}
