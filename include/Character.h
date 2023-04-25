#ifndef __CHARACTER__H__
#define __CHARACTER__H__

#include "Room.h"
#include "GameObject.h"

class Character : public GameObject {
public:
	// An example of how you do not need to define variable names in th declaration of a function
	// Only if you use them in a function do they need to be named.
	Character(const std::string&, const std::string&, const std::string&);

	virtual bool IsCharacter() const { return true; }

	virtual void SetCurrentRoom(SharedRoomPtr room) { this->current_room = room; }
	virtual SharedRoomPtr GetCurrentRoom() const { return current_room; }

	virtual void Look();
	virtual void clear() { current_room = nullptr; }
protected:
	SharedRoomPtr current_room = nullptr;
};

#endif  //!__CHARACTER__H__
