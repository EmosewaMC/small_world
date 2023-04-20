#include "Character.h"

#include "Room.h"
#include "Logger.h"

void Character::set_current_room(SharedRoomPtr room) {
	current_room = room;
}

SharedRoomPtr Character::get_current_room() {
	return current_room;
}

void Character::look() {
	if (!current_room) {
		Log("You are nowhere");
		return;
	}
	Log("%s\n", current_room->get_description().c_str());
}


