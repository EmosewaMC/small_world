#ifndef __QUEUE__H__
#define __QUEUE__H__

#include <mutex>
#include <string>
#include <vector>

#define LockQueue std::lock_guard<std::mutex> lock(m_Mutex)

class Queue {
public:
	Queue() = default;
	~Queue() = default;

	std::string GetMessage();
	void AddMessage(std::string& message);
	bool Empty();
private:
	std::mutex m_Mutex;
	std::vector<std::string> m_Queue;
};

#endif  //!__QUEUE__H__
