#ifndef __QUEUE__H__
#define __QUEUE__H__

#include <mutex>
#include <string>
#include <vector>
class BaseMessage;

#define LockQueue std::lock_guard<std::mutex> lock(m_Mutex)

class Queue {
public:
	Queue() = default;
	~Queue() = default;

	BaseMessage* GetMessage();
	void QueueMessage(BaseMessage* message);
	bool Empty();
private:
	std::mutex m_Mutex;
	std::vector<BaseMessage*> m_Queue;
};

#endif  //!__QUEUE__H__
