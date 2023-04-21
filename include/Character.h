#ifndef __CHARACTER__H__
#define __CHARACTER__H__

#include "Room.h"
#include "GameObject.h"

class Character : public GameObject {
public:
	Character(const std::string& id_, const std::string& name_, const std::string& desc_);

	virtual bool IsCharacter() const { return true; }

	virtual void SetCurrentRoom(SharedRoomPtr room) { this->current_room = room; }
	virtual SharedRoomPtr GetCurrentRoom() const { return current_room; }

	virtual void Look();
	virtual void clear() { current_room = nullptr; }
protected:
	SharedRoomPtr current_room = nullptr;
};

#endif  //!__CHARACTER__H__
