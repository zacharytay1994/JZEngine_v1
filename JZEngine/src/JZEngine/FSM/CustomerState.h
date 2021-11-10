#pragma once

#include "State.h"
#include "FiniteStateMachine.h"
//#include "../DebugTools/PerformanceData.h"
#include <iostream>
#include "../Input/Input.h"
#include "../DebugTools/DebugNew.h"

namespace JZEngine
{
	//float dt = 1.0f / PerformanceData::app_fps_;

	//Use class to make the enums strongly typed and the enums are scoped
	//to prevent acciental misuse of constants incase there are similar names
	enum class CustomerStateType
	{
		ORDERING,
		WAITING,
		ANGRYLEAVE,
		HAPPYLEAVE
	};

	class CustomerOrderingState : public State<CustomerStateType>
	{
	public:
		CustomerOrderingState(FiniteStateMachine<CustomerStateType>& fsm)
			: State<CustomerStateType>(CustomerStateType::ORDERING, "Ordering")
			, mFsm{ fsm }
			, timer{0.0f}
		{

		}

		void enter() override
		{
			timer = 0.0f;
			std::cout << "Customer state: ORDERING" << "\n";
		}

		void update(float dt) override
		{
			timer += dt;

			if (timer > 3.0f)
			{
				std::cout << "Done ordering, transition to waiting state!" << "\n";
				mFsm.setCurrentState(CustomerStateType::WAITING);
			}

			//std::cout << "timer: " << timer << "\n";
		}


	private:
		FiniteStateMachine<CustomerStateType>& mFsm;
		float timer;

	};

	class CustomerWaitingState : public State<CustomerStateType>
	{
	public:
		CustomerWaitingState(FiniteStateMachine<CustomerStateType>& fsm)
			: State<CustomerStateType>(CustomerStateType::WAITING, "Waiting")
			, mFsm{ fsm }
			, timer{ 0.0f }
		{

		}

		void enter() override
		{
			isCompleted = false;
			timer = 0.0f;
			std::cout << "Customer state: WAITING" << "\n";
		}

		void update(float dt) override
		{
			timer += dt;

			if (InputHandler::IsKeyTriggered(KEY::KEY_M))
			{
				isCompleted = true;
			}

			if (timer > 6.0f)
			{
				std::cout << "Wait too long! ANGRY!" << "\n";
				mFsm.setCurrentState(CustomerStateType::ANGRYLEAVE);
			}
			else if (isCompleted == true)
			{
				std::cout << "Completed order in time! Yay!" << "\n";
				mFsm.setCurrentState(CustomerStateType::HAPPYLEAVE);
			}
		}

	private:
		FiniteStateMachine<CustomerStateType>& mFsm;
		float timer;
		bool isCompleted = false;

	};

	class CustomerAngryLeaveState : public State<CustomerStateType>
	{
	public:
		CustomerAngryLeaveState(FiniteStateMachine<CustomerStateType>& fsm)
			: State<CustomerStateType>(CustomerStateType::ANGRYLEAVE, "AngryLeave")
			, mFsm{ fsm }
		{

		}

		void enter() override
		{
			std::cout << "Customer state: ANGRYLEAVE" << "\n";
		}

	private:
		FiniteStateMachine<CustomerStateType>& mFsm;
	};

	class CustomerHappyLeaveState : public State<CustomerStateType>
	{
	public:
		CustomerHappyLeaveState(FiniteStateMachine<CustomerStateType>& fsm)
			: State<CustomerStateType>(CustomerStateType::HAPPYLEAVE, "HappyLeave")
			, mFsm{ fsm }
		{

		}

		void enter() override
		{
			std::cout << "Customer state: HAPPYLEAVE" << "\n";
		}

	private:
		FiniteStateMachine<CustomerStateType>& mFsm;
	};


} //JZEngine namespace