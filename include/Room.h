#ifndef __ROOM__H__
#define __ROOM__H__

#include <string> 
#include <map>
#include <memory>

#include "GameObject.h"

class Room : public GameObject {
protected:

	// all of the items in this room
	std::map<std::string, SharedGameObjectPtr> contents;

	// a map which links a symbolic direction, like "north" to the id of another room
	// when the player types "go north" we will use this to lookup what room to transit to
	std::map<std::string, std::string> links_to_other_rooms;

public:
	Room(const std::string& id_, const std::string name_, const std::string& desc_): GameObject(id_, name_, desc_) {}

	virtual bool is_room() const { return true; }

	virtual bool add_contents(SharedGameObjectPtr object) {
		if (!object->is_character() && !object->is_item()) return false;
		contents[object->get_id()] = object;
		return true;
	}

	virtual void remove_contents(SharedGameObjectPtr object) {
		contents.erase(object->get_id());
	}

	virtual void add_link(const std::string& direction, const std::string& to_id) {
		links_to_other_rooms[direction] = to_id;
	}

	virtual std::string get_link(const std::string& direction);
	virtual void clear();
	virtual std::string get_next_room_id(const std::string& direction);
};

typedef std::shared_ptr<Room> SharedRoomPtr;

#endif  //!__ROOM__H__
