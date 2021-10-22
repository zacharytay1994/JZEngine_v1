#include "PCH.h"
#include "State.h"
#include "FiniteStateMachine.h"
#include <iostream>

namespace JZEngine
{
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
			if ()
		}


	private:
		FiniteStateMachine<CustomerStateType>& mFsm;


	};


} //JZEngine namespace