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
	Nothing
};

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

std::unordered_map<std::string, CustomerSpriteData> customer_animations {
	{"ahma_idle",		{7.0f, 7.0f, 1, 12, 12, 0.1f} },
	{"ahma_angry",		{7.0f, 7.0f, 1, 18, 18, 0.1f} },
	{"ahma_ordering",	{7.0f, 7.0f, 1, 21, 21, 0.1f} },
	{"ahma_success",	{7.0f, 7.0f, 1, 9, 9, 0.1f}	  },
	{"bigguy_idle",		{7.0f, 7.0f, 1, 12, 12, 0.1f} },
	{"bigguy_angry",	{7.0f, 7.0f, 1, 15, 15, 0.1f} },
	{"bigguy_ordering",	{7.0f, 7.0f, 1, 9, 9, 0.1f} },
	{"bigguy_success",	{7.0f, 7.0f, 1, 8, 8, 0.1f} },
	{"tallguy_idle",	{7.0f, 11.0f, 1, 13, 13, 0.1f} },
	{"tallguy_angry",	{7.0f, 11.0f, 1, 17, 17, 0.1f} },
	{"tallguy_ordering",{7.0f, 11.0f, 1, 18, 18, 0.1f} },
	{"tallguy_success",	{7.0f, 11.0f, 1, 9, 9, 0.1f} }
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
	if (name == "ahma")
	{
		anims.animations_[0] = "ahma_idle";
		anims.animations_[1] = "ahma_angry";
		anims.animations_[2] = "ahma_ordering";
		anims.animations_[3] = "ahma_success";
	}
	else if (name == "bigguy")
	{

		anims.animations_[0] = "bigguy_idle";
		anims.animations_[1] = "bigguy_angry";
		anims.animations_[2] = "bigguy_ordering";
		anims.animations_[3] = "bigguy_success";
	}
	else if (name == "tallguy")
	{

		anims.animations_[0] = "tallguy_idle";
		anims.animations_[1] = "tallguy_angry";
		anims.animations_[2] = "tallguy_ordering";
		anims.animations_[3] = "tallguy_success";
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

struct Customer
{
	int scene_object_id_{ -1 };			// the scene object it will be controlling
	float max_wait_time_{ 30.0f };		// will only wait for 30 secs
	float angry_wait_time_{ 13.0f };	// angry when 13 secs left
	float wait_time_{ 0.0f };			// countdown to how long it has waited
	bool angry_{ false };
	bool active_{ true };
	int animation_id_ { -1 };

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
		int order = rand() % 4;
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
			if (transform->child_position_.x < 0.0f)
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
					Scene ().GetComponent<JZEngine::NonInstanceShader> ( "Customer" , scene_object_id_ )->tint.x = 0.7f;
					JZEngine::Log::Info("Main", "Customer {} got angry.", scene_object_id_);
					took_too_long_ = true;
					//SetCustomerAnimation("ahma_angry", scene_object_id_);
					//SetCustomerAnimation(animation_pack_, AnimationStates::Angry, scene_object_id_);
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
float customer_delay_{ 5.0f };
float queue_timer_{ customer_delay_};

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
			customers.erase(i);
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

bool InteractWithQueue(bool food, CustomerOrder order)
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
			if (order == customer.order_)
			{
				// success
				SetCustomerAnimation(customer.animation_pack_, AnimationStates::Success, customer.scene_object_id_);
				customer.state_ = CustomerState::Success;
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
			SetCustomerAnimation(customer.animation_pack_, AnimationStates::Ordering, customer.scene_object_id_);

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

CustomerOrder GetNextCustomerOrder()
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
	customer_delay_ = 5.0f;
	queue_timer_ = customer_delay_;

	queue_layer = Scene().GetComponent<JZEngine::SpriteLayer>("Queue")->layer_;
	// set all customers to false
	for (int i = 0; i < number_of_customers; ++i)
	{
		customer_ids.push(i);
		Scene().EntityFlagActive("Customer", false, i);
		Scene().GetComponent<JZEngine::Transform>("Customer", i)->child_position_.x = out_queue_position_;
	}
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
			queue_timer_ = 5.0f + static_cast<float>( rand () % 3 + 1);
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