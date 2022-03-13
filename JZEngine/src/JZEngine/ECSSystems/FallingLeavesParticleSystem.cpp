#include <PCH.h>
#include "FallingLeavesParticleSystem.h"

#include "../ECS/ECSConfig.h"
#include "../Resource/ObjectPool.h"

namespace JZEngine
{
	LeafParticle::LeafParticle ()
	{
		RegisterComponents<Transform , LeafParticleComponent> ();
	}

	void LeafParticle::Update ( const float& dt )
	{
		LeafParticleComponent& lpc = GetComponent<LeafParticleComponent> ();
		if ( !lpc.has_texture )
		{
			lpc.has_texture = true;
			int rand_texture = ( rand () % 3 ) + 1;
			std::stringstream ss;
			ss << "LeafDay0" << rand_texture << "_ParticleEffect_Hawker";
			GetComponent<JZEngine::Texture> ().texture_id_ = ResourceManager::GetTextureID ( ss.str () );
		}

		Transform& transform = GetComponent<Transform> ();
		transform.position_ += ( lpc.wind_direction_ + lpc.mass_ * lpc.gravity_ ) * dt;
		transform.position_ += 1.0f * sin ( lpc.life_ );
		//transform.scale_.x = lpc.scale_x_ * sin ( lpc.life_ );
		transform.rotation_ += sin ( lpc.life_ * 0.5f ) * Math::PI/2.0f;

		if ( lpc.life_ <= 0.0f )
		{
			lpc.life_ = lpc.lifetime_;
			lpc.has_texture = false;
			ToggleActiveFlag ( false );
		}
		else
		{
			lpc.life_ -= dt;
		}
	}

	LeafParticleSystem::LeafParticleSystem ()
	{
		RegisterComponents<Transform , LeafParticleSystemComponent> ();
	}

	void LeafParticleSystem::Init ()
	{
	}

	void LeafParticleSystem::Update ( const float& dt )
	{
		LeafParticleSystemComponent& lpsc = GetComponent<LeafParticleSystemComponent> ();
		if ( lpsc.timer_ > lpsc.emission_rate_ )
		{
			ECS::Entity& e = ObjectPool::GetNewEntity ( ecs_instance_ , "LeafParticle" );

			// eg particle system code
			e.GetComponent<Transform> ().position_ = GetComponent<Transform> ().position_;
			LeafParticleComponent& lpc = e.GetComponent<LeafParticleComponent> ();
			Transform& lp_transform = e.GetComponent<Transform> ();

			float low = -lpsc.wind_spread_ , high = lpsc.wind_spread_;
			float spread = low + static_cast < float > ( rand () ) / ( static_cast < float > ( RAND_MAX / ( high - low ) ) );
			lpc.wind_direction_ = Math::GetRotatedVector ( Vec2f ( 1.0f , 0.0f ) , lpsc.wind_direction_ + spread );
			lpc.wind_direction_ *= lpsc.wind_speed_;

			float max_scale = 1.5f;
			float rand_scale = static_cast < float > ( rand () ) / ( static_cast < float > ( RAND_MAX / max_scale ) );
			lpc.mass_ = 1.0f + rand_scale * 10.0f;
			lp_transform.scale_.x = 1.0f + rand_scale;
			lp_transform.scale_.y = 1.0f + rand_scale;
			lpc.scale_x_ = 1.0f + rand_scale;

			float max_rotation = 360.0f;
			float rand_rotation = static_cast < float > ( rand () ) / ( static_cast < float > ( RAND_MAX / max_rotation ) );
			lp_transform.rotation_ = rand_rotation;

			lpsc.timer_ = 0.0f;
		}
		else
		{
			lpsc.timer_ += dt;
		}
	}
}