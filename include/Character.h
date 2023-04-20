#ifndef __CHARACTER__H__
#define __CHARACTER__H__

#include "Room.h"
#include "GameObject.h"

class Character : public GameObject {
public:
	Character(const std::string& id_, const std::string& name_, const std::string& desc_);

	virtual bool is_character() const { return true; }

	virtual void set_current_room(SharedRoomPtr room);
	virtual SharedRoomPtr get_current_room();

	virtual void look();
	virtual void clear() { current_room = nullptr; }
protected:
	SharedRoomPtr current_room = nullptr;
};

#endif  //!__CHARACTER__H__
