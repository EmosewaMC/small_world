#include "Queue.h"
#include "Logger.h"

std::string Queue::GetMessage() {
	LockQueue;
	if (m_Queue.empty()) {
		LogWarning("Queue is empty");
		return "";
	}
	std::string message = m_Queue.front();
	m_Queue.erase(m_Queue.begin());
	return message;
}

void Queue::AddMessage(std::string& message) {
	LockQueue;
	m_Queue.push_back(message);
}

bool Queue::Empty() {
	LockQueue;
	return m_Queue.empty();
}
