#include "Room.h"
#include "Index.h"

std::string Room::GetLink(const std::string& direction) {
	// "" is the "error value"
	auto it = links_to_other_rooms.find(direction);
	return it == links_to_other_rooms.end() ? "" : it->second;
}

void Room::Clear() {
	contents.clear();
	links_to_other_rooms.clear();
}

std::string Room::GetNextRoomId(const std::string& direction) {
	auto it = links_to_other_rooms.find(direction);
	return it == links_to_other_rooms.end() ? "" : it->second;
}


