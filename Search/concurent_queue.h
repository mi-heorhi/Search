#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T> class ConcurentQueue
{
public:
	void push(T const &val)
	{
		lock l(_mutex);
		bool wake = _queue.empty();
		_queue.push(val);
		if (wake) _condition.notify_one();
	}

	T pop()
	{
		ulock u(_mutex);
		while (_queue.empty())
			_condition.wait(u);
		T retval = _queue.front();
		_queue.pop();
		return retval;
	}
	bool empty()
	{
		return _queue.empty();
	}
private:
	std::queue<T> _queue;
	std::mutex _mutex;
	std::condition_variable _condition;

	typedef std::lock_guard<std::mutex> lock;
	typedef std::unique_lock<std::mutex> ulock;
};