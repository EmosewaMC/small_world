#ifndef __INTERFACEMANAGER__H__
#define __INTERFACEMANAGER__H__

#include <cstdint>

#define SendMessage(message) InterfaceManager::iSendMessage(&message, __FILE__, __LINE__, __FUNCTION__)

class BaseMessage;

namespace InterfaceManager {
	bool iSendMessage(BaseMessage* message, const char* file, uint32_t line, const char* function);
};

#endif  //!__INTERFACEMANAGER__H__
