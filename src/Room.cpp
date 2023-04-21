#include "Room.h"
#include "Index.h"

std::string Room::GetLink(const std::string& direction) {
	// "" is the "error value"
	auto it = links_to_other_rooms.find(direction);
	if (it == links_to_other_rooms.end()) return "";

	return it->second;
}

void Room::clear() {
	contents.clear();
	links_to_other_rooms.clear();
}

std::string Room::GetNextRoomId(const std::string& direction) {
	std::map<std::string, std::string>::iterator it = links_to_other_rooms.find(direction);
	if (it == links_to_other_rooms.end()) return "";
	return it->second;
}


