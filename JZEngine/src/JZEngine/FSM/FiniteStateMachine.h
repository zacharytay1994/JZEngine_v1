#pragma once

#include "../FSM/State.h"
#include <map>
#include <cassert>
#include "../DebugTools/DebugNew.h"

namespace JZEngine
{
	template <typename T>
	class FiniteStateMachine
	{
	protected:

		//A map to represent a set of states
		std::map<T, State<T>*> mStates;

		//The current state
		State<T>* mCurrentState;

	public:
		FiniteStateMachine() : mCurrentState(nullptr) {}

		//Add states
		void add(State<T>* state)
		{
			if (state != nullptr)
			{
				mStates[state->getID()] = state;
			}
		}

		void add(T stateID, State<T>* state)
		{
			mStates.add(stateID, state);
		}

		State<T>* getState(T stateID)
		{
			return mStates[stateID];
		}

		State<T>* getCurrentState()
		{
			return mCurrentState;
		}

		void setCurrentState(T stateID)
		{
			State<T>* state = getState(stateID);

			//Abort program execution if setCurrentState calls 0 as parameter
			assert(state != nullptr&& "Abort program execution if setCurrentState calls 0 as parameter");

			setCurrentState(state);
		}

		void setCurrentState(State<T>* state)
		{
			if (mCurrentState == state)
			{
				return;
			}

			if (mCurrentState != nullptr)
			{
				mCurrentState->exit();
			}

			mCurrentState = state;

			if (mCurrentState != nullptr)
			{
				mCurrentState->enter();
			}
		}

		void update(float dt)
		{
			if (mCurrentState != nullptr)
			{
				mCurrentState->update(dt);
			}
		}

		~FiniteStateMachine()
		{
			for (const auto& state : mStates)
			{
				//second is State<T>*
				delete state.second;
			}
		
		}

	};

} //JZEngine namespace
