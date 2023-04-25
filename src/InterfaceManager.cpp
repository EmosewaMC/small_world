#include "InterfaceManager.h"
#include "BaseMessage.h"

#include "Logger.h"
bool InterfaceManager::iSendMessage(BaseMessage* message, const char* file, uint32_t line, const char* function) {
	message->SetFile(file);
	message->SetLine(line);
	message->SetFunction(function);
	Log("Sending message with source %s %i %s to target %s", message->GetFile(), message->GetLine(), message->GetFunction(), message->GetTarget().c_str());
	return true;
}
