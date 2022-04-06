/*	__FILE HEADER__
*	File:		HawkerQueue.h
	Primary:	Zachary Tay
	Date:		19/06/21
	Brief:		Queue logic.
*/

#pragma once

#include <JZEngine.h>
#include <vector>
#include <stdlib.h>
#include <unordered_map>
#include <string>
#include <stack>

enum class DAY
{
	ONE ,
	TWO ,
	THREE
};
DAY hawker_scene_day = DAY::TWO;

enum class CustomerState
{
	WalkingIn,
	Waiting,
	Success,
	WalkingOut
};

enum class CustomerOrder
{
	Wanton,
	SeaweedChicken,
	SpringRoll,
	CarrotCake,
	ChickenFeet,
	HarGao,
	SiewMai,
	CharSiewBao,
	DouShaBao,
	CoffeeBao,
	PlainCCF,
	PrawnCCF,
	Nothing
};

unsigned int num_springroll {8};
unsigned int num_dumpling {7};
unsigned int num_carrotcake {9};
unsigned int num_seaweedchicken {8};

unsigned int rnum_springroll;
unsigned int rnum_dumpling;;
unsigned int rnum_carrotcake;
unsigned int rnum_seaweedchicken;

// day 2 
unsigned int num_chickenfeet { 3 };
unsigned int num_hargao { 3 };
unsigned int num_siewmai { 3 };
unsigned int num_charsiewbao { 3 };
unsigned int num_doushabao { 3 };
unsigned int num_coffeebao { 3 };

unsigned int rnum_chickenfeet { 3 };
unsigned int rnum_hargao { 3 };
unsigned int rnum_siewmai { 3 };
unsigned int rnum_charsiewbao { 3 };
unsigned int rnum_doushabao { 3 };
unsigned int rnum_coffeebao { 3 };

// day 2
unsigned int num_plainccf { 5 };
unsigned int num_prawnccf { 5 };

unsigned int rnum_plainccf { 5 };
unsigned int rnum_prawnccf { 5 };

int max_customers { 0 };
int num_customers { 0 };

int GetRandomOrder ()
{
	bool find { true };
	while ( find )
	{
		if ( num_customers <= 0 )
		{
			return 0;
		}
		int rand_order{0};
		if ( hawker_scene_day == DAY::ONE )
		{
			rand_order = rand () % 4;
		}
		else if ( hawker_scene_day == DAY::TWO )
		{
			rand_order = rand () % 10;
		}
		else if ( hawker_scene_day == DAY::THREE )
		{
			rand_order = rand () % 12;
		}

		switch ( rand_order )
		{
			// springroll
		case ( 0 ):
			if ( rnum_springroll > 0 )
			{
				--rnum_springroll;
				--num_customers;
				return rand_order;
			}
			break;
		case ( 1 ):
			if ( rnum_dumpling > 0 )
			{
				--rnum_dumpling;
				--num_customers;
				return rand_order;
			}
			break;
		case ( 2 ):
			if ( rnum_carrotcake > 0 )
			{
				--rnum_carrotcake;
				--num_customers;
				return rand_order;
			}
			break;
		case ( 3 ):
			if ( rnum_seaweedchicken > 0 )
			{
				--rnum_seaweedchicken;
				--num_customers;
				return rand_order;
			}
			break;
		// day 2
		case ( 4 ):
			if ( rnum_chickenfeet > 0 )
			{
				--rnum_chickenfeet;
				--num_customers;
				return rand_order;
			}
			break;
		case ( 5 ):
			if ( rnum_hargao > 0 )
			{
				--rnum_hargao;
				--num_customers;
				return rand_order;
			}
			break;
		case ( 6 ):
			if ( rnum_siewmai > 0 )
			{
				--rnum_siewmai;
				--num_customers;
				return rand_order;
			}
			break;
		case ( 7 ):
			if ( rnum_charsiewbao > 0 )
			{
				--rnum_charsiewbao;
				--num_customers;
				return rand_order;
			}
			break;
		case ( 8 ):
			if ( rnum_doushabao > 0 )
			{
				--rnum_doushabao;
				--num_customers;
				return rand_order;
			}
			break;
		case ( 9 ):
			if ( rnum_coffeebao > 0 )
			{
				--rnum_coffeebao;
				--num_customers;
				return rand_order;
			}
			break;
		// day 3
		case ( 10 ):
			if ( rnum_plainccf > 0 )
			{
				--rnum_plainccf;
				--num_customers;
				return rand_order;
			}
			break;
		case ( 11 ):
			if ( rnum_prawnccf > 0 )
			{
				--rnum_prawnccf;
				--num_customers;
				return rand_order;
			}
			break;
		}
	}
	return -1;
}

std::stack<int> customer_ids;

void RemoveCustomer(int id);

struct CustomerSpriteData
{
	float x_scale_;
	float y_scale_;
	int rows_;
	int cols_;
	int max_frames_;
	float animation_speed_;
};

enum class AnimationStates
{
	Idle,
	Angry,
	Ordering, 
	Success
};

//name of spritesheet, size width, size height, row, column, total frames, framespeed)
std::unordered_map<std::string, CustomerSpriteData> customer_animations {
	{"1_AhMa(Idle)_SpriteSheet_Hawker",		{13.24f * 0.75f, 9.56f * 0.75f, 4, 4, 13, 0.1f}  },
	{"1_AhMa(Angry)_SpriteSheet_Hawker",	{13.24f * 0.75f, 9.56f * 0.75f, 5, 6, 27, 0.1f} },
	{"1_AhMa(Ordering)_SpriteSheet_Hawker",	{13.24f * 0.75f, 9.56f * 0.75f, 4, 6, 21, 0.1f} },
	{"1_AhMa(Success)_SpriteSheet_Hawker",	{13.24f * 0.75f, 9.56f * 0.75f, 3, 6, 17, 0.1f} },
	{"2_AhMa(Idle)_SpriteSheet_Hawker",		{13.24f * 0.75f, 9.56f * 0.75f, 4, 4, 13, 0.1f}  },
	{"2_AhMa(Angry)_SpriteSheet_Hawker",	{13.24f * 0.75f, 9.56f * 0.75f, 5, 6, 27, 0.1f} },
	{"2_AhMa(Ordering)_SpriteSheet_Hawker",	{13.24f * 0.75f, 9.56f * 0.75f, 4, 6, 21, 0.1f} },
	{"2_AhMa(Success)_SpriteSheet_Hawker",	{13.24f * 0.75f, 9.56f * 0.75f, 3, 6, 17, 0.1f} },
	{"3_AhMa(Idle)_SpriteSheet_Hawker",		{13.24f * 0.75f, 9.56f * 0.75f, 4, 4, 13, 0.1f}  },
	{"3_AhMa(Angry)_SpriteSheet_Hawker",	{13.24f * 0.75f, 9.56f * 0.75f, 5, 6, 27, 0.1f} },
	{"3_AhMa(Ordering)_SpriteSheet_Hawker",	{13.24f * 0.75f, 9.56f * 0.75f, 4, 6, 21, 0.1f} },
	{"3_AhMa(Success)_SpriteSheet_Hawker_ver2",	{13.24f * 0.75f, 9.56f * 0.75f, 3, 6, 17, 0.1f} },



	{"1_BigGuy(Idle)_SpriteSheet_Hawker",		{12.14f * 0.75f, 9.56f * 0.75f, 2, 6, 12, 0.1f} },
	{"1_BigGuy(angry)_SpriteSheet_Hawker",	{12.14f * 0.75f, 9.56f * 0.75f, 4, 6, 24, 0.1f} },
	{"1_BigGuy(Ordering)_SpriteSheet_Hawker",	{12.14f * 0.75f, 9.56f * 0.75f, 3, 6, 14, 0.1f} },
	{"1_BigGuy(Success)_SpriteSheet_Hawker",	{12.14f * 0.75f, 9.56f * 0.75f, 3, 6, 17, 0.1f} },
		{"2_BigGuy(Idle)_SpriteSheet_Hawker",		{12.14f * 0.75f, 9.56f * 0.75f, 2, 6, 12, 0.1f} },
	{"2_BigGuy(angry)_SpriteSheet_Hawker",	{12.14f * 0.75f, 9.56f * 0.75f, 4, 6, 24, 0.1f} },
	{"2_BigGuy(Ordering)_SpriteSheet_Hawker",	{12.14f * 0.75f, 9.56f * 0.75f, 3, 6, 14, 0.1f} },
	{"2_BigGuy(Success)_SpriteSheet_Hawker",	{12.14f * 0.75f, 9.56f * 0.75f, 3, 6, 17, 0.1f} },
		{"3_BigGuy(Idle)_SpriteSheet_Hawker",		{12.14f * 0.75f, 9.56f * 0.75f, 2, 6, 12, 0.1f} },
	{"3_BigGuy(angry)_SpriteSheet_Hawker",	{12.14f * 0.75f, 9.56f * 0.75f, 4, 6, 24, 0.1f} },
	{"3_BigGuy(Ordering)_SpriteSheet_Hawker",	{12.14f * 0.75f, 9.56f * 0.75f, 3, 6, 14, 0.1f} },
	{"3_BigGuy(Success)_SpriteSheet_Hawker",	{12.14f * 0.75f, 9.56f * 0.75f, 3, 6, 17, 0.1f} },

	{"1_TallGuy(Idle)_SpriteSheet_Hawker",	{8.14f, 13.42f, 3, 6, 13, 0.1f} },
	{"1_TallGuy(angry)_SpriteSheet_Hawker",	{8.14f, 13.42f, 5, 6, 25, 0.1f} },
	{"1_TallGuy(Ordering)_SpriteSheet_Hawker",{8.14f, 13.42f, 4, 6, 19, 0.1f} },
	{"1_TallGuy(Success)_SpriteSheet_Hawker",	{8.14f, 13.42f, 3, 6, 17, 0.1f} },
	{"2_TallGuy(Idle)_SpriteSheet_Hawker",	{8.14f, 13.42f, 3, 6, 13, 0.1f} },
	{"2_TallGuy(angry)_SpriteSheet_Hawker",	{8.14f, 13.42f, 5, 6, 25, 0.1f} },
	{"2_TallGuy(Ordering)_SpriteSheet_Hawker",{8.14f, 13.42f, 4, 6, 19, 0.1f} },
	{"2_TallGuy(Success)_SpriteSheet_Hawker",	{8.14f, 13.42f, 3, 6, 17, 0.1f} },
	{"3_TallGuy(Idle)_SpriteSheet_Hawker",	{8.14f, 13.42f, 3, 6, 13, 0.1f} },
	{"3_TallGuy(angry)_SpriteSheet_Hawker",	{8.14f, 13.42f, 5, 6, 25, 0.1f} },
	{"3_TallGuy(Ordering)_SpriteSheet_Hawker",{8.14f, 13.42f, 4, 6, 19, 0.1f} },
	{"3_TallGuy(Success)_SpriteSheet_Hawker",	{8.14f, 13.42f, 3, 6, 17, 0.1f} },



};

struct AnimationPack
{
	AnimationStates state_{ AnimationStates::Idle };
	AnimationStates last_state_{ AnimationStates::Idle };
	std::string animations_[4];
};
//using AnimationPack = std::string[4];

void BuildAnimationPack(AnimationPack& anims, const std::string& name)
{
	int rand_colour;
	rand_colour = rand() % 3;
	if (rand_colour == 0)
	{
		if (name == "ahma")
		{
			anims.animations_[0] = "1_AhMa(Idle)_SpriteSheet_Hawker";
			anims.animations_[1] = "1_AhMa(Angry)_SpriteSheet_Hawker";
			anims.animations_[2] = "1_AhMa(Ordering)_SpriteSheet_Hawker";
			anims.animations_[3] = "1_AhMa(Success)_SpriteSheet_Hawker";
		}
		else if (name == "bigguy")
		{

			anims.animations_[0] = "1_BigGuy(Idle)_SpriteSheet_Hawker";
			anims.animations_[1] = "1_BigGuy(angry)_SpriteSheet_Hawker";
			anims.animations_[2] = "1_BigGuy(Ordering)_SpriteSheet_Hawker";
			anims.animations_[3] = "1_BigGuy(Success)_SpriteSheet_Hawker";
		}
		else if (name == "tallguy")
		{

			anims.animations_[0] = "1_TallGuy(Idle)_SpriteSheet_Hawker";
			anims.animations_[1] = "1_TallGuy(angry)_SpriteSheet_Hawker";
			anims.animations_[2] = "1_TallGuy(Ordering)_SpriteSheet_Hawker";
			anims.animations_[3] = "1_TallGuy(Success)_SpriteSheet_Hawker";
		}
	}
	else if (rand_colour == 1)
	{
		if (name == "ahma")
		{
			anims.animations_[0] = "2_AhMa(Idle)_SpriteSheet_Hawker";
			anims.animations_[1] = "2_AhMa(Angry)_SpriteSheet_Hawker";
			anims.animations_[2] = "2_AhMa(Ordering)_SpriteSheet_Hawker";
			anims.animations_[3] = "2_AhMa(Success)_SpriteSheet_Hawker";
		}
		else if (name == "bigguy")
		{

			anims.animations_[0] = "2_BigGuy(Idle)_SpriteSheet_Hawker";
			anims.animations_[1] = "2_BigGuy(angry)_SpriteSheet_Hawker";
			anims.animations_[2] = "2_BigGuy(Ordering)_SpriteSheet_Hawker";
			anims.animations_[3] = "2_BigGuy(Success)_SpriteSheet_Hawker";
		}
		else if (name == "tallguy")
		{

			anims.animations_[0] = "2_TallGuy(Idle)_SpriteSheet_Hawker";
			anims.animations_[1] = "2_TallGuy(angry)_SpriteSheet_Hawker";
			anims.animations_[2] = "2_TallGuy(Ordering)_SpriteSheet_Hawker";
			anims.animations_[3] = "2_TallGuy(Success)_SpriteSheet_Hawker";
		}
	}
	else if (rand_colour == 2)
	{
		if (name == "ahma")
		{
			anims.animations_[0] = "3_AhMa(Idle)_SpriteSheet_Hawker";
			anims.animations_[1] = "3_AhMa(Angry)_SpriteSheet_Hawker";
			anims.animations_[2] = "3_AhMa(Ordering)_SpriteSheet_Hawker";
			anims.animations_[3] = "3_AhMa(Success)_SpriteSheet_Hawker";
		}							
		else if (name == "bigguy")	
		{							
									
			anims.animations_[0] = "3_BigGuy(Idle)_SpriteSheet_Hawker";
			anims.animations_[1] = "3_BigGuy(angry)_SpriteSheet_Hawker";
			anims.animations_[2] = "3_BigGuy(Ordering)_SpriteSheet_Hawker";
			anims.animations_[3] = "3_BigGuy(Success)_SpriteSheet_Hawker";
		}							
		else if (name == "tallguy")	
		{							
									
			anims.animations_[0] = "3_TallGuy(Idle)_SpriteSheet_Hawker";
			anims.animations_[1] = "3_TallGuy(angry)_SpriteSheet_Hawker";
			anims.animations_[2] = "3_TallGuy(Ordering)_SpriteSheet_Hawker";
			anims.animations_[3] = "3_TallGuy(Success)_SpriteSheet_Hawker";
		}
	}

}

void SetCustomerAnimation(AnimationPack& animPack, AnimationStates state, int id)
{
	std::string animation = animPack.animations_[static_cast<int>(state)];
	animPack.last_state_ = animPack.state_;
	animPack.state_ = state;
	if (customer_animations.find(animation) != customer_animations.end())
	{
		CustomerSpriteData& csd = customer_animations[animation];
		Scene().GetComponent<JZEngine::Texture>("Customer", id)->texture_id_ = Scene().GetTexture(animation);
		JZEngine::Transform* transform = Scene().GetComponent<JZEngine::Transform>("Customer", id);
		transform->scale_.x = customer_animations[animation].x_scale_;
		transform->scale_.y = customer_animations[animation].y_scale_;
		JZEngine::Animation2D* anim = Scene().GetComponent<JZEngine::Animation2D>("Customer", id);
		anim->column_ = csd.cols_;
		anim->rows_ = csd.rows_;
		anim->max_frames_ = csd.max_frames_;
		anim->animation_speed_ = csd.animation_speed_;
		anim->frame_ = 0;
	}
}

float out_queue_position_{ -800.0f };
bool took_too_long_ { false };
float customer_spacing_ = { 100.0f };

bool hawker_queue_display_order_toggle { false };

struct Customer
{
	int scene_object_id_{ -1 };			// the scene object it will be controlling
	float max_wait_time_{ 30.0f };		// will only wait for 30 secs
	float angry_wait_time_{ 13.0f };	// angry when 13 secs left
	float wait_time_{ 0.0f };			// countdown to how long it has waited
	bool angry_{ false };
	bool active_{ true };
	int animation_id_ { -1 };

	int position_in_queue_ { -1 };
	bool no_food_ { false };

	CustomerOrder order_{ CustomerOrder::Wanton };
	AnimationPack animation_pack_;

	static constexpr float walk_speed_ = 1000.0f;
	
	CustomerState state_ = CustomerState::WalkingIn;

	Customer(int id, int customerInFront)
		:
		scene_object_id_{id},
		wait_time_{max_wait_time_}
	{
		Scene().EntityFlagActive("Customer", true, scene_object_id_); 
		// position customer
		JZEngine::Transform* transform = Scene().GetComponent<JZEngine::Transform>("Customer", scene_object_id_);
		transform->child_position_ = { 0.0f,0.0f };
		// set a random order for the customer
		//int order = rand() % 4;
		int order = GetRandomOrder();
		order_ = static_cast<CustomerOrder>(order);
		JZEngine::Log::Info("Main", "Order: {}.", order);

		transform->child_position_.x = out_queue_position_;

		int customer_rand;
		while ( ( customer_rand = rand () % 3 ) == customerInFront );
		animation_id_ = customer_rand;
		if (customer_rand == 0)
		{
			BuildAnimationPack(animation_pack_, "ahma");
		}
		else if (customer_rand == 1)
		{
			BuildAnimationPack(animation_pack_, "bigguy");
		}
		else if (customer_rand == 2)
		{
			BuildAnimationPack(animation_pack_, "tallguy");
		}
		SetCustomerAnimation(animation_pack_, AnimationStates::Idle, scene_object_id_);

		Scene ().GetComponent<JZEngine::NonInstanceShader> ( "Customer" , scene_object_id_ )->tint.x = 0.0f;
	}

	void Update(float dt)
	{
		if (!active_)
		{
			// stop processing customer, flag inactive and return it to queue
			RemoveCustomer(scene_object_id_);
		}

		// if animation state is ordering or success check if frame up and set back to idle
		if (animation_pack_.state_ == AnimationStates::Ordering || animation_pack_.state_ == AnimationStates::Angry  )
		{
			JZEngine::Animation2D* anim = Scene().GetComponent<JZEngine::Animation2D>("Customer", scene_object_id_);
			if (anim->frame_ >= anim->max_frames_ - 1)
			{
				SetCustomerAnimation(animation_pack_, animation_pack_.last_state_, scene_object_id_);
			}
		}

		JZEngine::Transform* transform = Scene().GetComponent<JZEngine::Transform>("Customer", scene_object_id_);
		JZEngine::Animation2D* anim = Scene().GetComponent<JZEngine::Animation2D>("Customer", scene_object_id_);

		switch (state_)
		{
		case CustomerState::WalkingIn:
			// walk in 
			if (transform->child_position_.x < -( customer_spacing_ * position_in_queue_ ) )
			{
				transform->child_position_.x += walk_speed_ * dt;
			}
			else
			{
				state_ = CustomerState::Waiting;
			}
			break;
		case CustomerState::Waiting:
			if (wait_time_ > 0.0f)
			{
				wait_time_ -= dt;
				// if time to get angry
				if (!angry_ && wait_time_ < angry_wait_time_)
				{
					angry_ = true;
					Scene ().GetComponent<JZEngine::NonInstanceShader> ( "Customer" , scene_object_id_ )->tint.x = 0.337f;
					JZEngine::Log::Info("Main", "Customer {} got angry.", scene_object_id_);
					took_too_long_ = true;
					//SetCustomerAnimation("ahma_angry", scene_object_id_);
					//SetCustomerAnimation(animation_pack_, AnimationStates::Angry, scene_object_id_);
				}

				// move to new position
				if ( transform->child_position_.x < -( customer_spacing_ * position_in_queue_ ) )
				{
					transform->child_position_.x += walk_speed_ * dt;
				}
			}
			else
			{
				// remove from queue, walk out
				state_ = CustomerState::WalkingOut;
			}
			break;
		case CustomerState::Success:
			if (anim->frame_ >= anim->max_frames_ - 1)
			{
				SetCustomerAnimation(animation_pack_, AnimationStates::Idle, scene_object_id_);
				state_ = CustomerState::WalkingOut;
				hawker_queue_display_order_toggle = true;
			}
			break;
		case CustomerState::WalkingOut:
			if (transform->child_position_.x > out_queue_position_)
			{
				transform->child_position_.x -= walk_speed_ * dt;
			}
			else
			{
				Scene ().GetComponent<JZEngine::NonInstanceShader> ( "Customer" , scene_object_id_ )->tint.x = 0.0f;
				active_ = false;
			}
			break;
		}
	}
};

int queue_layer{ 0 };
int number_of_customers{ 5 };
std::vector<Customer> customers;
float customer_delay_{ 5.5f };
float queue_timer_{ customer_delay_};
int customers_in_queue_ { 0 };

bool NewCustomer()
{
	if (customer_ids.size() > 0)
	{
		if ( customers.empty () )
		{
			customers.emplace_back ( customer_ids.top () , -1 );
		}
		else
		{
			customers.emplace_back ( customer_ids.top () , customers.back ().animation_id_ );
		}
		customers.back().position_in_queue_ = customers_in_queue_++;
		JZEngine::Log::Info("Main", "Customer came. ID: {}.", customer_ids.top());
		customer_ids.pop();
		return true;
	}
	return false;
}

void RemoveCustomer(int id)
{
	for (auto i = customers.begin(); i != customers.end();)
	{
		if (i->scene_object_id_ == id)
		{
			// decrement all customers behind queue number
			for ( auto& j : customers )
			{
				if ( j.position_in_queue_ > i->position_in_queue_ )
				{
					--j.position_in_queue_;
				}
			}
			--customers_in_queue_;

			i = customers.erase(i);
			Scene().EntityFlagActive("Customer", false, id);
			customer_ids.push(id);
			JZEngine::Log::Info("Main", "Customer left. ID: {}.", id);
			JZEngine::Transform* transform = Scene().GetComponent<JZEngine::Transform>("Customer", id);
			transform->child_position_.x = out_queue_position_;
			return;
		}
		else
		{
			++i;
		}
	}
}

bool InteractWithQueue(bool food, CustomerOrder order, bool giveMeWin)
{
	// find next customer that has not been successfully served
	Customer* p_customer{ nullptr };
	for (int i = 0; i < customers.size(); ++i)
	{
		if (customers[i].state_ != CustomerState::Success && customers[i].state_ != CustomerState::WalkingOut)
		{
			p_customer = &customers[i];
			break;
		}
	}
	if (p_customer)
	{
		if (food)
		{
			Customer& customer = *p_customer;
			if (order == customer.order_ || giveMeWin)
			{
				// success
				SetCustomerAnimation(customer.animation_pack_, AnimationStates::Success, customer.scene_object_id_);
				customer.state_ = CustomerState::Success; 
				Scene ().GetComponent<JZEngine::NonInstanceShader> ( "Customer" , customer.scene_object_id_ )->tint.x = 0.0f;
				JZEngine::Log::Info("Main", "Order success to customer {}", customer.scene_object_id_);
				return true;
			}
			else
			{
				SetCustomerAnimation ( customer.animation_pack_ , AnimationStates::Angry , customer.scene_object_id_ );
			}
		}
		else
		{
			// display order
			Customer& customer = *p_customer;
			if ( customer.no_food_ )
			{
				SetCustomerAnimation ( customer.animation_pack_ , AnimationStates::Angry , customer.scene_object_id_ );
				customer.state_ = CustomerState::Success;
				JZEngine::Log::Info ( "Main" , "No Food to customer {}" , customer.scene_object_id_ );
			}
			else
			{
				SetCustomerAnimation ( customer.animation_pack_ , AnimationStates::Ordering , customer.scene_object_id_ );
			}

			// debug code
			switch (customer.order_)
			{
			case CustomerOrder::Wanton:
				JZEngine::Log::Info("Main", "Customer order is Wanton.");
				break;
			case CustomerOrder::SeaweedChicken:
				JZEngine::Log::Info("Main", "Customer order is SeaweedChicken.");
				break;
			case CustomerOrder::SpringRoll:
				JZEngine::Log::Info("Main", "Customer order is SpringRoll.");
				break;
			case CustomerOrder::CarrotCake:
				JZEngine::Log::Info("Main", "Customer order is CarrotCake.");
				break;
			}
		}
	}
	return false;
}

CustomerOrder GetNextCustomerOrder(int dumpling, int seaweed, int carrotcake, int popiah,
	int charsiewbao, int doushabao, int coffeebao, int siewmai, int hargow, int chickenfeet)
{
	Customer* p_customer{ nullptr };
	for (int i = 0; i < customers.size(); ++i)
	{
		if (customers[i].state_ != CustomerState::Success && customers[i].state_ != CustomerState::WalkingOut)
		{
			p_customer = &customers[i];
			break;
		}
	}
	if (p_customer)
	{
		switch ( p_customer->order_ )
		{
		case CustomerOrder::CarrotCake:
			if ( carrotcake <= 0 )
			{
				p_customer->no_food_ = true;
			}
			break;
		case CustomerOrder::Wanton:
			if ( dumpling <= 0 )
			{
				p_customer->no_food_ = true;
			}
			break;
		case CustomerOrder::SeaweedChicken:
			if ( seaweed <= 0 )
			{
				p_customer->no_food_ = true;
			}
			break;
		case CustomerOrder::SpringRoll:
			if ( popiah <= 0 )
			{
				p_customer->no_food_ = true;
			}
			break;
		// day 2
		case CustomerOrder::CharSiewBao:
			if ( charsiewbao <= 0 )
			{
				p_customer->no_food_ = true;
			}
			break;
		case CustomerOrder::DouShaBao:
			if ( doushabao <= 0 )
			{
				p_customer->no_food_ = true;
			}
			break;
		case CustomerOrder::CoffeeBao:
			if ( coffeebao <= 0 )
			{
				p_customer->no_food_ = true;
			}
			break;
		case CustomerOrder::SiewMai:
			if ( siewmai <= 0 )
			{
				p_customer->no_food_ = true;
			}
			break;
		case CustomerOrder::HarGao:
			if ( hargow <= 0 )
			{
				p_customer->no_food_ = true;
			}
			break;
		case CustomerOrder::ChickenFeet:
			if ( chickenfeet <= 0 )
			{
				p_customer->no_food_ = true;
			}
			break;
		}
		return p_customer->order_;
	}
	return CustomerOrder::Nothing;
}

void InitHawkerQueue()
{
	// initialize all data
	customer_ids = std::stack<int>();
	out_queue_position_ = -800.0f;
	queue_layer = 0;
	number_of_customers = 5;
	customers = std::vector<Customer>();
	customer_delay_ = 2.5f;
	queue_timer_ = customer_delay_;

	queue_layer = Scene().GetComponent<JZEngine::SpriteLayer>("Queue")->layer_;
	// set all customers to false
	for (int i = 0; i < number_of_customers; ++i)
	{
		customer_ids.push(i);
		Scene().EntityFlagActive("Customer", false, i);
		Scene().GetComponent<JZEngine::Transform>("Customer", i)->child_position_.x = out_queue_position_;
	}

	rnum_springroll = num_springroll + ( ( rand () % 5 ) - 2 );
	rnum_carrotcake = num_carrotcake + ( ( rand () % 5 ) - 2 );
	rnum_dumpling = num_dumpling + ( ( rand () % 5 ) - 2 );
	rnum_seaweedchicken = num_seaweedchicken + ( ( rand () % 5 ) - 2 );

	max_customers = rnum_springroll + rnum_carrotcake + rnum_dumpling + rnum_seaweedchicken;
	if ( hawker_scene_day == DAY::TWO )
	{
		max_customers += rnum_chickenfeet + rnum_hargao + rnum_siewmai + rnum_coffeebao + rnum_doushabao + rnum_charsiewbao;
	}
	num_customers = max_customers;

	hawker_queue_display_order_toggle = false;
}

void UpdateHawkerQueue(float dt)
{
	if (queue_timer_ > 0.0f)
	{
		queue_timer_ -= dt;
	}
	else
	{
		if (NewCustomer())
		{
			// set queue timer to rand 5-8 secs
			queue_timer_ = customer_delay_ + static_cast<float>( rand () % 3 + 1);
		}
	}

	// process customers
	int i = 0;
	for (auto& customer : customers)
	{
		customer.Update(dt);
		// set customer layer based on order in queue
		Scene().GetComponent<JZEngine::SpriteLayer>("Customer", customer.scene_object_id_)->layer_ = queue_layer - i;
		++i;
	}
}