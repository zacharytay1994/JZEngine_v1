/*	__FILE HEADER__
*	File:		ThreadPool.cpp
	Primary:	Jee Jia Min
	Date:		24/11/21
	Brief:		Thread pool implementation.
*/

#include <PCH.h>
#include "ThreadPool.h"
#include <stdlib.h>		/* exit, EXIT_FAILURE (to be replaced with JZAssert) */
#include <string>		/* string */

namespace JZEngine
{
	void SetThreadName ( DWORD dwThreadID , const char* threadName )
	{
		THREADNAME_INFO info;
		info.dwType = 0x1000;
		info.szName = threadName;
		info.dwThreadID = dwThreadID;
		info.dwFlags = 0;
#pragma warning(push)
#pragma warning(disable: 6320 6322)
		__try
		{
			RaiseException ( MS_VC_EXCEPTION , 0 , sizeof ( info ) / sizeof ( ULONG_PTR ) , ( ULONG_PTR* ) &info );
		}
		__except( EXCEPTION_EXECUTE_HANDLER )
		{
		}
#pragma warning(pop)
	}

	ThreadPool::ThreadPool ( const size_t threads_count )
	{
		const size_t concurrent_threads_ = std::thread::hardware_concurrency ();

		/**
		 * hardware_concurrency returns the number of concurrent
		 threads supported by the implementation .
		*/
		if( threads_count > concurrent_threads_ )
		{
			std::cout << "Allocation of thread counts " << threads_count << "is more than concurrent threads supported" << concurrent_threads_ << " .\n";
			exit ( EXIT_FAILURE );
		}

		threads_.resize ( threads_count );

		int counter{ 0 };
		for( std::thread& th : threads_ )
		{
			th = std::thread ( ThreadPool::TaskConsumer , this );
			std::string name = "JZ::ThreadPool" + std::to_string ( counter++ );

			// change thread name by getting the DWORD (unsigned long) .
			DWORD threadId = GetThreadId ( static_cast< HANDLE >( th.native_handle () ) );
			SetThreadName ( threadId , name.c_str () );
		}
	}

	ThreadPool::~ThreadPool ()
	{
		{
			std::unique_lock <std::mutex> locker ( lock_mutex_ );
			is_thread_pool_in_destruction_ = true ;

			while( !tasks_queue_.empty () )
			{
				tasks_queue_.pop ();
			}
		}

		// notify all the threads about the closing
		event_obj_.notify_all ();

		// bind eof of threads to main thread
		for( std::thread& th : threads_ )
		{
			th.join ();
		}

#ifdef ThreadPoolDebug
		std::cout << "ThreadPool ~ThreadPool() - Tasks Queue Size : " << tasks_queue_.size () << std::endl;
#endif
	}

	void ThreadPool::TaskConsumer ( ThreadPool* pool )
	{
		// infinity consume and execute tasks
		while( true )
		{
			std::function<void ()> task = [] ()
			{};
			{
				// lock guard
				std::unique_lock < std::mutex > locker ( pool->lock_mutex_ );

				/**
				 * @brief
				 * Wait causes the current thread to block until the
				 condition variable is notified or a spurious wakeup
				 occurs, optionally looping until some predicate is
				 satisfied (bool(stop_waiting()) == true).
				 * @param pool
				 * Predicate which returns ​false if the waiting should
				 be continued.
				*/
				pool->event_obj_.wait ( locker , [pool] ()
				{
					// if queue have items or pool is in destruction we exit from wait state
					return pool->is_thread_pool_in_destruction_ || !pool->tasks_queue_.empty ();
				} );


				// if pool is in destruction leave end current thread
				if( pool->is_thread_pool_in_destruction_ )
					return;

				// if we have items in queue, pop task
				task = pool->tasks_queue_.front (); pool->tasks_queue_.pop ();
			}
			// execute task
			task () ;
		}
	}

	ThreadPool& ThreadPool::Instance ()
	{
		// classic singleton
		static ThreadPool pool; // classic singleton
		return pool;
	}

	size_t ThreadPool::ThreadCapacity ()
	{
		// lock guard
		std::unique_lock < std::mutex > locker ( lock_mutex_ );
		return threads_.size ();
	}

	size_t ThreadPool::ThreadQueueTaskCount ()
	{
		std::unique_lock < std::mutex > locker ( lock_mutex_ );
		return tasks_queue_.size ();
	}
}