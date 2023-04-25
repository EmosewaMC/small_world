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
		if (!object->IsCharacter() && !object->IsItem()) return false;
		contents[object->GetId()] = object;
		return true;
	}

	virtual void RemoveContents(SharedGameObjectPtr object) {
		contents.erase(object->GetId());
	}

	virtual void AddLink(const std::string& direction, const std::string& to_id) {
		links_to_other_rooms[direction] = to_id;
	}

	virtual std::string GetLink(const std::string& direction);
	virtual void Clear();
	virtual std::string GetNextRoomId(const std::string& direction);
};

typedef std::shared_ptr<Room> SharedRoomPtr;

#endif  //!__ROOM__H__
