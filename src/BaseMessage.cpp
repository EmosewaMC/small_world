#include "BaseMessage.h"

BaseMessage::BaseMessage() {
	this->file = __FILE__;
	this->line = __LINE__;
	this->function = __FUNCTION__;
	this->targetId = "";
}
