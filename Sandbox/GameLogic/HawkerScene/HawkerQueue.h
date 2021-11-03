#pragma once

#include <vector>

//typedef unsigned int Customers;
//
//std::queue<Customers> hawker_queue;
//
//float angry_customer_time = 2.0f;
//float angry_customer_timer = angry_customer_time;
//int out = -1;
//int in = -1;
//float customer_horizontal_speed = 1600.0f;
//float customer_vertical_speed = 80.0f;
//float space_between_customers = 10.0f;
//
//void InitHawkerQueue() {
//	angry_customer_time = 2.0f;
//	angry_customer_timer = angry_customer_time;
//	out = -1;
//	in = -1;
//	customer_horizontal_speed = 1600.0f;
//	customer_vertical_speed = 80.0f;
//	hawker_queue = std::queue<Customers>();
//
//	// Get queue entity
//	JZEngine::ECS::Entity* e = Scene().GetEntity("Queue");
//	int queue_layer = Scene().GetComponent<JZEngine::SpriteLayer>("Queue")->layer_;
//	//int queue_y = e.GetComponentEX<JZEngine::Transform>().position_.y;
//	for (int i = 0; i < static_cast<int>(e->children_count_); ++i)
//	{
//		// set customer layer offset from the queue layer
//		Scene().GetComponent<JZEngine::SpriteLayer>("Customer", i)->layer_ = queue_layer - i;
//		// offset customer y to make it seem like it is behind
//		Scene().GetComponent<JZEngine::Transform>("Customer", i)->child_position_.y = space_between_customers * i;
//		// push into queue
//		hawker_queue.push(i);
//	}
//}
//
//void UpdateHawkerQueue(float dt)
//{
//	// remove a customer every 2 secs and add to the back
//	if (angry_customer_timer < 0.0f)
//	{
//		// remove the first customer
//		if (out == -1)
//		{
//			out = hawker_queue.front();
//			hawker_queue.pop();
//		}
//		angry_customer_timer = angry_customer_time;
//	}
//	else
//	{
//		angry_customer_timer -= dt;
//	}
//	// if has customer walking out
//	if (out != -1)
//	{
//		JZEngine::Vec2f& position = Scene().GetComponent<JZEngine::Transform>("Customer", out)->child_position_;
//		if (position.x > -1200.0f)
//		{
//			position.x -= customer_horizontal_speed * dt;
//		}
//		else
//		{
//			// if finished walking out, walk in
//			// set position and layer to the back
//			position.y = hawker_queue.size() * space_between_customers;
//			Scene().GetComponent<JZEngine::SpriteLayer>("Customer", out)->layer_ = 
//				Scene().GetComponent<JZEngine::SpriteLayer>("Queue")->layer_ - static_cast<int>(hawker_queue.size());
//			//in = out;
//			out = -1;
//		}
//	}
//	// if has customer walking in
//	if (in != -1)
//	{
//		JZEngine::Vec2f& position = Scene().GetComponent<JZEngine::Transform>("Customer", in)->child_position_;
//		if (position.x < 0.0f)
//		{
//			position.x += customer_horizontal_speed * dt;
//		}
//		else
//		{
//			// if finished walking in, add customer to queue
//			hawker_queue.push(in);
//			in = -1;
//		}
//	}
//	// move all customers in queue to position
//	std::queue<Customers> temp_queue = hawker_queue;
//	int queue_layer = Scene().GetComponent<JZEngine::SpriteLayer>("Queue")->layer_;
//	for (int i = 0; i < temp_queue.size(); ++i)
//	{
//		int customer = hawker_queue.front();
//		hawker_queue.pop();
//		// move into position
//		JZEngine::Vec2f& position = Scene().GetComponent<JZEngine::Transform>("Customer", customer)->child_position_;
//		if (position.y > i * space_between_customers)
//		{
//			position.y -= customer_vertical_speed * dt;
//		}
//		else
//		{
//			// set the layer
//			Scene().GetComponent<JZEngine::SpriteLayer>("Customer", customer)->layer_ = queue_layer - i;
//		}
//	}
//	hawker_queue = temp_queue;
//}

enum class CustomerState
{
	WalkingIn,
	Waiting,
	WalkingOut
};

std::stack<int> customer_ids;

void RemoveCustomer(int id);

struct Customer
{
	int scene_object_id_{ -1 };	// the scene object it will be controlling
	float max_wait_time_{ 10.0f };		// will only wait for 30 secs
	float angry_wait_time_{ 6.0f };	// angry when 13 secs left
	float wait_time_{ 0.0f };			// countdown to how long it has waited
	bool angry_{ false };
	bool active_{ true };
	
	CustomerState state_ = CustomerState::WalkingIn;

	Customer(int id)
		:
		scene_object_id_{id},
		wait_time_{max_wait_time_}
	{
		Scene().EntityFlagActive("Customer", true, scene_object_id_); 
		// position customer
		Scene().GetComponent<JZEngine::Transform>("Customer", scene_object_id_)->child_position_ = { 0.0f,0.0f };
	}

	void Update(float dt)
	{
		if (!active_)
		{
			// stop processing customer, flag inactive and return it to queue
			RemoveCustomer(scene_object_id_);
		}

		switch (state_)
		{
		case CustomerState::WalkingIn:
			// walk in 
			state_ = CustomerState::Waiting;
			break;
		case CustomerState::Waiting:
			if (wait_time_ > 0.0f)
			{
				wait_time_ -= dt;
				// if time to get angry
				if (!angry_ && wait_time_ < angry_wait_time_)
				{
					angry_ = true;
				}
			}
			else
			{
				// remove from queue, walk out
				state_ = CustomerState::WalkingOut;
			}
			break;
		case CustomerState::WalkingOut:
			active_ = false;
			break;
		}
	}
};

int number_of_customers{ 5 };
std::vector<Customer> customers;
float customer_delay_{ 5.0f };
float queue_timer_{ customer_delay_};

void NewCustomer()
{
	if (customer_ids.size() > 0)
	{
		customers.push_back(customer_ids.top());
		customer_ids.pop();
	}
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
			JZEngine::Log::Info("Main", "Customer removed.");
		}
		else
		{
			++i;
		}
	}
}

void InitHawkerQueue()
{
	// set all customers to false
	for (int i = 0; i < number_of_customers; ++i)
	{
		customer_ids.push(i);
		Scene().EntityFlagActive("Customer", false, i);
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
		NewCustomer();
		queue_timer_ = customer_delay_;
		JZEngine::Log::Info("Main", "Customer added.");
	}

	// process customers
	for (auto& customer : customers)
	{
		customer.Update(dt);
	}
}