#include <PCH.h>
#include "Text.h"
#include "../ECS/ECSConfig.h"

namespace JZEngine
{
	Text::Text ()
	{
		RegisterComponents<TextData , Transform> ();
	}

	void Text::Update ( const float& dt )
	{
		if( text_renderer_ )
		{
			Transform& transform = GetComponent<Transform> ();
			TextData& text_data = GetComponent<TextData> ();

			text_renderer_->RenderText ( "temp" , text_data.position_.x + transform.position_.x , text_data.position_.y + transform.position_.y , text_data.scale_ , { 0.0f,0.0f,0.0f } );
		}
	}
}