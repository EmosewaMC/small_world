#include "Character.h"

#include "Room.h"
#include "Logger.h"

Character::Character(const std::string& id_, const std::string& name_, const std::string& desc_): GameObject(id_, name_, desc_) {}

void Character::look() {
	if (!current_room) {
		LogError("You are nowhere");
		return;
	}
	Message("%s\n", current_room->get_description().c_str());
}


