#ifndef __GOACTION__H__
#define __GOACTION__H__

#include "BaseMessage.h"
#include "MessageIdentifiers.h"
#include <string>

class Go : public BaseMessage {
public:
	Go() {
		msgId = MessageIdentifiers::GO;
		direction = "";
	}
	virtual ~Go() = default;

	const std::string& GetDirection() const { return direction; }
	void SetDirection(const std::string& direction) { this->direction = direction; }
private:
	std::string direction;
};

#endif  //!__GOACTION__H__
