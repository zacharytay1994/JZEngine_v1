#pragma once

#include <queue>

typedef unsigned int Customers;

std::queue<Customers> hawker_queue;

float angry_customer_time = 2.0f;
float angry_customer_timer = angry_customer_time;
int out = -1;
int in = -1;
float customer_horizontal_speed = 1600.0f;
float customer_vertical_speed = 80.0f;
float space_between_customers = 10.0f;

void InitHawkerQueue() {
	angry_customer_time = 2.0f;
	angry_customer_timer = angry_customer_time;
	out = -1;
	in = -1;
	customer_horizontal_speed = 1600.0f;
	customer_vertical_speed = 80.0f;
	hawker_queue = std::queue<Customers>();

	// Get queue entity
	JZEngine::ECS::Entity* e = Scene().GetEntity("Queue");
	int queue_layer = Scene().GetComponent<JZEngine::SpriteLayer>("Queue")->layer_;
	//int queue_y = e.GetComponentEX<JZEngine::Transform>().position_.y;
	for (int i = 0; i < static_cast<int>(e->children_count_); ++i)
	{
		// set customer layer offset from the queue layer
		Scene().GetComponent<JZEngine::SpriteLayer>("Customer", i)->layer_ = queue_layer - i;
		// offset customer y to make it seem like it is behind
		Scene().GetComponent<JZEngine::Transform>("Customer", i)->child_position_.y = space_between_customers * i;
		// push into queue
		hawker_queue.push(i);
	}
}

void UpdateHawkerQueue(float dt)
{
	// remove a customer every 2 secs and add to the back
	if (angry_customer_timer < 0.0f)
	{
		// remove the first customer
		if (out == -1)
		{
			out = hawker_queue.front();
			hawker_queue.pop();
		}
		angry_customer_timer = angry_customer_time;
	}
	else
	{
		angry_customer_timer -= dt;
	}
	// if has customer walking out
	if (out != -1)
	{
		JZEngine::Vec2f& position = Scene().GetComponent<JZEngine::Transform>("Customer", out)->child_position_;
		if (position.x > -1200.0f)
		{
			position.x -= customer_horizontal_speed * dt;
		}
		else
		{
			// if finished walking out, walk in
			// set position and layer to the back
			position.y = hawker_queue.size() * space_between_customers;
			Scene().GetComponent<JZEngine::SpriteLayer>("Customer", out)->layer_ = 
				Scene().GetComponent<JZEngine::SpriteLayer>("Queue")->layer_ - static_cast<int>(hawker_queue.size());
			in = out;
			out = -1;
		}
	}
	// if has customer walking in
	if (in != -1)
	{
		JZEngine::Vec2f& position = Scene().GetComponent<JZEngine::Transform>("Customer", in)->child_position_;
		if (position.x < 0.0f)
		{
			position.x += customer_horizontal_speed * dt;
		}
		else
		{
			// if finished walking in, add customer to queue
			hawker_queue.push(in);
			in = -1;
		}
	}
	// move all customers in queue to position
	std::queue<Customers> temp_queue = hawker_queue;
	int queue_layer = Scene().GetComponent<JZEngine::SpriteLayer>("Queue")->layer_;
	for (int i = 0; i < temp_queue.size(); ++i)
	{
		int customer = hawker_queue.front();
		hawker_queue.pop();
		// move into position
		JZEngine::Vec2f& position = Scene().GetComponent<JZEngine::Transform>("Customer", customer)->child_position_;
		if (position.y > i * space_between_customers)
		{
			position.y -= customer_vertical_speed * dt;
		}
		else
		{
			// set the layer
			Scene().GetComponent<JZEngine::SpriteLayer>("Customer", customer)->layer_ = queue_layer - i;
		}
	}
	hawker_queue = temp_queue;
}