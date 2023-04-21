#include "GameObject.h"

GameObject::GameObject(const std::string& id, const std::string& name, const std::string& description) {
	this->id = id;
	this->name = name;
	this->description = description;
}
