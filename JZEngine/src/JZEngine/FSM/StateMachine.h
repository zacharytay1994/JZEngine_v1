#pragma once

#include <string>
#include <map>
#include <cassert>

namespace JZEngine
{
	template <typename T>
	class State
	{
	public:

		//Use inline for small/one liner function in header file to increase compilation time
		inline T getID()
		{
			return mID;
		}

		inline const std::string& getName() const
		{
			return mName;
		}

		//Use explicit to avoid any implicit conversion
		explicit State(T id, std::string name = "default") : mName{ name }, mID{ id } {};

		virtual void enter()
		{
			//To be overwritten in a derived class
		}

		virtual void exit()
		{
			//To be overwritten in a derived class
		}

		virtual void update()
		{
			//To be overwritten in a derived class
		}

	private:
		std::string mName;
		T mID;
	};


	template <typename T>
	class FiniteStateMachine
	{
	protected:

		//A map to represent a set of states
		std::map<T, State<T>*> mStates;

		//The current state
		State<T>* mCurrentState;

	public:
		FiniteStateMachine() : mCurrentState(0) {}

		//Add states
		void add(State<T>* state)
		{
			if (state == 0)
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
			assert(state != 0);

			setCurrentState(state);
		}

		void setCurrentState(State<T>* state)
		{
			if (mCurrentState == state)
			{
				return;
			}

			if (mCurrentState != 0)
			{
				mCurrentState->exit();
			}

			mCurrentState = state;

			if (mCurrentState != 0)
			{
				mCurrentState->enter();
			}
		}

		void update()
		{
			if (mCurrentState != 0)
			{
				mCurrentState->update();
			}
		}

	};



} //JZEngine namespace
