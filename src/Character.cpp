#include "Character.h"

#include "Room.h"
#include "Logger.h"

Character::Character(const std::string& id, const std::string& name, const std::string& desc): GameObject(id, name, desc) {}

void Character::Look() {
	if (!current_room) {
		LogError("You are nowhere? How?");
		return;
	}
	Message("%s\n", current_room->GetDescription().c_str());
}


