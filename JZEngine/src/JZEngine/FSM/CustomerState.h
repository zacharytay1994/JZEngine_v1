#pragma once

#include "State.h"
#include "FiniteStateMachine.h"
#include "../DebugTools/PerformanceData.h"
#include <iostream>

namespace JZEngine
{
	float dt = 1.0f / PerformanceData::app_fps_;

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
		{

		}

		void enter()
		{
			std::cout << "Customer state: ORDERING" << "\n";
		}

		void update()
		{
			if (JZEngine::dt > 3.0f)
			{
				std::cout << "Done ordering, transition to waiting state!" << "\n";
				mFsm.setCurrentState(CustomerStateType::WAITING);
			}
		}


	private:
		FiniteStateMachine<CustomerStateType>& mFsm;

	};

	class CustomerWaitingState : public State<CustomerStateType>
	{
	public:
		CustomerWaitingState(FiniteStateMachine<CustomerStateType>& fsm)
			: State<CustomerStateType>(CustomerStateType::WAITING, "Waiting")
			, mFsm{ fsm }
		{

		}

		void enter()
		{
			std::cout << "Customer state: WAITING" << "\n";
		}

		void update()
		{
			if (JZEngine::dt > 6.0f)
			{
				std::cout << "Wait too long! ANGRY!" << "\n";
				mFsm.setCurrentState(CustomerStateType::ANGRYLEAVE);
			}
			else if (JZEngine::dt <= 6.0f)
			{
				std::cout << "Completed order in time! Yay!" << "\n";
				mFsm.setCurrentState(CustomerStateType::HAPPYLEAVE);
			}
		}

	private:
		FiniteStateMachine<CustomerStateType>& mFsm;

	};


} //JZEngine namespace