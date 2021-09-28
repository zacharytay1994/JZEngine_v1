#include <PCH.h>
#include "ExampleFloatAway.h"
#include "../ECS/ECSConfig.h"
#include "../Input/Input.h"

namespace JZEngine
{
	//  flaot unicorn
	FloatAwayAllUnicorn::FloatAwayAllUnicorn()
	{
		RegisterComponents <JZEngine::Transform, JZEngine::InstanceShader, IsUnicorn>();
	}

	void FloatAwayAllUnicorn::Update( const float& dt )
	{
		//float y = static_cast < float > ( rand() ) / static_cast < float > ( RAND_MAX );
		GetComponent<Transform>().position_.y += dt * 10.0f;
	}

	// input unicorn
	MakeUnicornAffectedByInput::MakeUnicornAffectedByInput()
	{
		RegisterComponents <JZEngine::Transform, JZEngine::InstanceShader, IsUnicorn, IsInputAffected>();
	}

	void MakeUnicornAffectedByInput::Update( const float& dt )
	{
		if ( InputHandler::IsKeyPressed( KEY::KEY_LEFT ) )
		{
			GetComponent<Transform>().position_.x -= GetComponent<IsInputAffected>().val;
		}
		if ( InputHandler::IsKeyPressed( KEY::KEY_RIGHT ) )
		{
			GetComponent<Transform>().position_.x += GetComponent<IsInputAffected>().val;
		}
		if ( InputHandler::IsKeyPressed( KEY::KEY_UP ) )
		{
			GetComponent<Transform>().position_.y += GetComponent<IsInputAffected>().val;
		}
		if ( InputHandler::IsKeyPressed( KEY::KEY_DOWN ) )
		{
			GetComponent<Transform>().position_.y -= GetComponent<IsInputAffected>().val;
		}
	}
}
