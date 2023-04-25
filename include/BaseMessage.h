#ifndef __BASEMESSAGE__H__
#define __BASEMESSAGE__H__

#include <cstdint>
#include <string>

enum class MessageIdentifiers : uint32_t;

class BaseMessage {
public:
	BaseMessage();
	virtual ~BaseMessage() = default;

	const char* GetFile() const { return file; }
	void SetFile(const char* file) { this->file = file; }

	uint32_t GetLine() const { return line; }
	void SetLine(uint32_t line) { this->line = line; }

	const char* GetFunction() const { return function; }
	void SetFunction(const char* function) { this->function = function; }
	
	const std::string& GetTarget() const { return targetId; }
	void SetTarget(const std::string& target) { this->targetId = target; }

	MessageIdentifiers GetMsgId() const { return msgId; }
protected:
	std::string targetId;
	MessageIdentifiers msgId;
	const char* file;
	uint32_t line;
	const char* function;
};

#endif  //!__BASEMESSAGE__H__
