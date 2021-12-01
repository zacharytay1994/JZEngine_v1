/*	__FILE HEADER__
*	File:		ThreadPool.h
	Primary:	Jee Jia Min
	Date:		24/11/21
	Brief:		Thread pool implementation.


* What this ThreadPool do ?
* Perform tasks without the cost of creating and destroying threads.
* Allows you to perform tasks in different modes: asynchronous and parallel.
* Performing functions with any number of parameters.

* How to use ?

* Example 1 :
	auto foo =  [](int a , int b){return a+b};
	thread_pool& pool = thread_pool::instance();
	int result = pool.async(func, 1, 2);

* Example 2 :
	class foo { public : void bar(){...} }
	foo obj;
	thread_pool& pool = thread_pool::instance();
	pool.async(&foo::bar, &obj, 2, 3);

* Example 3 :
	class foo
	{
	public :
		void bar()
		{
			thread_pool& pool = thread_pool::instance();
			pool.async(&foo::bar, *this , 2, 3);
		}
	}
*/

#pragma once

#ifdef _WIN32 /* Both 32 bit and 64 bit*/
#include <windows.h>
namespace JZEngine
{
	const DWORD MS_VC_EXCEPTION = 0x406D1388;
#pragma pack(push,8)
	typedef struct tagTHREADNAME_INFO
	{
		DWORD dwType;		// Must be 0x1000.
		LPCSTR szName;		// Pointer to name (in user addr space).
		DWORD dwThreadID;	// Thread ID (-1=caller thread).
		DWORD dwFlags;		// Reserved for future use, must be zero.
	} THREADNAME_INFO;
#pragma pack(pop)
	void SetThreadName ( DWORD dwThreadID , const char* threadName );
}
#endif

#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>
#include <vector>

// Uncomment the following define for debugging
#define ThreadPoolDebug 

namespace JZEngine
{
	class ThreadPool
	{
	private:

		/**
		 * @brief
		 * Synchronization primitive that can be used to block a
		 thread, or multiple threads at the same time, until
		 another thread both modifies a shared variable (the
		 condition), and notifies the condition_variable.
		*/
		std::condition_variable event_obj_ ;

		std::mutex lock_mutex_;

		std::atomic < bool > is_thread_pool_in_destruction_ = false ;

		/**
		 * @brief
		 * Fixed size array , will resize according to hardware
		 thread or prefix of 8 threads .
		*/
		std::vector < std::thread > threads_ ;

		/**
		 * @brief
		 * To store queue of free function.
		*/
		std::queue < std::function < void () > > tasks_queue_ ;

		/**
		* @brief
		* This is a private constructor.
		*/
		explicit ThreadPool ( const size_t threads_count = 2 );

		/**
		 * @brief
		 * To destruct thread pool
		*/
		~ThreadPool ();

		/**
		 * @brief
		 * Thread consume function
		 * @param pool
		*/
		static void TaskConsumer ( ThreadPool* pool );

	public:

		/**
		 * @brief
		 * return thread pool instance
		*/
		static ThreadPool& Instance ();


		/**
		 * @brief
		 * free all threads 
		*/
		void Free ();

		/**
		 * @brief
		 * return thread count in pool
		*/
		size_t ThreadCapacity ();

		/**
		 * @brief
		 * return queue task count
		*/
		size_t ThreadQueueTaskCount ();

		/**
		 * @brief			run function in parallel using thread from pool
		 * @tparam F		function type
		 * @tparam ...Args	function args list
		 * @param func		function for parallel execution
		 * @param ...args	function arguments
		 * @return			future result of executing function
		*/
		template < typename F , class ... Args>
		auto Parallel ( F&& func , Args && ... args )->std::future < std::invoke_result_t < F , Args ...>>
		{
			using return_type = std::invoke_result_t<F , Args...>;

			// create task
			auto task = std::make_shared<std::packaged_task<return_type ()>> ( std::bind ( std::forward<F> ( func ) , std::forward<Args> ( args )... ) );

			// get future result
			std::future<return_type> res = task->get_future ();

			{
				// lock guard
				std::unique_lock<std::mutex> locker ( this->lock_mutex_ );

				// add task do queue
				this->tasks_queue_.emplace ( [=]
				{
					( *task )( ); // execute task
				} );

#ifdef ThreadPoolDebug
				std::cout << "ThreadPool Parallel - Tasks Queue Size : " << tasks_queue_.size () << std::endl;
#endif

			}

			// notify one thread
			this->event_obj_.notify_one ();

			// return future result
			return res;
		}


		/**
		 * @brief			asynchronously execute function using thread from pool
		 * @tparam F		function type
		 * @tparam ...Args	function args list
		 * @param func		function for async execution
		 * @param ...args	function arguments
		 * @return			result of executing function
		*/
		template<typename F , class... Args>
		auto Async ( F&& func , Args&&... args ) -> std::invoke_result_t<F , Args...>
		{
			// get future result from existing
			std::future<std::invoke_result_t<F , Args...>> future_value = Parallel ( func , args... );

#ifdef ThreadPoolDebug
			std::cout << "ThreadPool Async - Tasks Queue Size : " << tasks_queue_.size () << std::endl;
#endif

			// return value contained in future value object
			return future_value.get ();
		}
	};
}