/*	__FILE HEADER__
*	File:		Text.cpp
	Primary:	Jee Jia Min
	Date:		01/07/21
	Brief:		ECS Text Renderer
*/

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

			text_renderer_->RenderText ( text_data.text.data , transform.position_.x , transform.position_.y , text_data.font_size_ , text_data.color_ , text_data.tracking_x_ , text_data.leading_y_);
		}
	}
}