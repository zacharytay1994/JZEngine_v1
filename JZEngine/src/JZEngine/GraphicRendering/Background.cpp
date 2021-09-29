#include <PCH.h>
#include "Background.h"
#include "../ECS/ECSConfig.h"

namespace JZEngine
{
	ParallaxBackground::ParallaxBackground ()
	{
		RegisterComponents<Transform , Texture , Parallax , NonInstanceShader> ();
	}
	void ParallaxBackground::Update ( const float& dt )
	{
		Transform& transform = GetComponent<Transform> ();
		Texture& texture = GetComponent<Texture> ();
		Parallax& background = GetComponent<Parallax> ();
		NonInstanceShader& shader = GetComponent<NonInstanceShader> ();

		float trans_x_ = transform.size_.x * transform.scale_.x;
		float trans_y_ = transform.size_.y * transform.scale_.y;

		if( background.is_vertical == false )
		{
			// X axis = Horizontal
			// check if texture size is more or less than window width 
			int repeat_right{ static_cast< int >( ( win_width_div2 - transform.position_.x ) / trans_x_ ) + 1 };
			int repeat_left{ static_cast< int >( ( win_width_div2 + transform.position_.x ) / trans_x_ ) + 1 };

			transform.position_.x += dt * background.speed_x_;

			// loop part
			if( transform.position_.x + ( trans_x_ / 2.0f ) < -win_width_div2 )
			{
				transform.position_.x = win_width_div2 + ( trans_x_ / 2.0f );
			}
			else if( transform.position_.x - ( trans_x_ / 2.0f ) > win_width_div2 )
			{
				transform.position_.x = -win_width_div2 - ( trans_x_ / 2.0f );
			}

			for( int i = 1 ; i <= repeat_right ; ++i )
			{
				sprite_renderer_.DrawSprite ( shader.shader_id_ , texture.texture_id_ ,
											  { transform.position_.x + ( trans_x_ * i ) , transform.position_.y } ,
											  transform.size_ , transform.scale_ ,
											  transform.rotation_ , { 1.0f,1.0f,1.0f } , shader.tint);
			}

			for( int i = 1 ; i <= repeat_left ; ++i )
			{
				sprite_renderer_.DrawSprite ( shader.shader_id_ , texture.texture_id_ ,
											  { transform.position_.x - ( trans_x_ * i ) , transform.position_.y } ,
											  transform.size_ , transform.scale_ , transform.rotation_ , { 1.0f,1.0f,1.0f }, shader.tint );
			}
		}

		if( background.is_vertical == true )
		{

			// Y axis = Vertical
			// check if texture size is more or less than window height 
			int repeat_top{ static_cast< int >( ( win_height_div2 - transform.position_.y ) / trans_y_ ) + 1 };
			int repeat_bottom{ static_cast< int >( ( win_height_div2 + transform.position_.y ) / trans_y_ ) + 1 };

			transform.position_.y += dt * background.speed_y_;

			// loop part
			if( transform.position_.y + ( trans_y_ / 2.0f ) < -win_height_div2 )
			{
				transform.position_.y = win_height_div2 + ( trans_y_ / 2.0f );
			}
			else if( transform.position_.y - ( trans_y_ / 2.0f ) > win_height_div2 )
			{
				transform.position_.y = -win_height_div2 - ( trans_y_ / 2.0f );
			}

			for( int i = 1 ; i <= repeat_top ; ++i )
			{
				sprite_renderer_.DrawSprite ( shader.shader_id_ , texture.texture_id_ ,
											  { transform.position_.x , transform.position_.y + ( trans_y_ * i ) } ,
											  transform.size_ , transform.scale_ , transform.rotation_ , { 1.0f,1.0f,1.0f }, shader.tint );
			}

			for( int i = 1 ; i <= repeat_bottom ; ++i )
			{
				sprite_renderer_.DrawSprite ( shader.shader_id_ , texture.texture_id_ ,
											  { transform.position_.x , transform.position_.y - ( trans_y_ * i ) } ,
											  transform.size_ , transform.scale_ , transform.rotation_ , { 1.0f,1.0f,1.0f }, shader.tint );
			}
		}

		sprite_renderer_.DrawSprite ( shader.shader_id_ , texture.texture_id_ , transform.position_ ,
									  transform.size_ , transform.scale_ , transform.rotation_ , { 1.0f,1.0f,1.0f } , shader.tint);

	}
}
