#include "Queue.h"

#include "BaseMessage.h"
#include "Logger.h"

BaseMessage* Queue::GetMessage() {
	LockQueue;
	if (m_Queue.empty()) {
		LogWarning("Queue is empty");
		return nullptr;
	}
	BaseMessage* message = m_Queue.front();
	m_Queue.erase(m_Queue.begin());
	return message;
}

void Queue::QueueMessage(BaseMessage* message) {
	LockQueue;
	m_Queue.push_back(message);
}

bool Queue::Empty() {
	LockQueue;
	return m_Queue.empty();
}
