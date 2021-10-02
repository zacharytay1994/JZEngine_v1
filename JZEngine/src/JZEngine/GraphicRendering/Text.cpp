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

			text_renderer_->RenderText ( "test" ,transform.position_.x , transform.position_.y , text_data.font_size_, { 0.0f,0.0f,0.0f } );
		}
	}
}