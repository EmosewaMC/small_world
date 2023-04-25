#ifndef __GAMEOBJECT__H__
#define __GAMEOBJECT__H__

#include <string>
#include <memory>

// A definition for the "root class" of objects in the system
// We have 3 properties; an id (unique amongst all objects we will load), a name
// (things can share the same name, but would have different IDs) and a description
// which is what we would see if we "look" at the object

// The root class would normally store all "properties" or "attributes" that
// are shared by ALL of the classes which inherit from it
//
// subclasses, like Player, Room, and Item add extra properties to this
// base definition

class GameObject {
protected:
	std::string id;
	std::string name;
	std::string description;

public:
	GameObject(const std::string& id, const std::string& name, const std::string& description);

	const std::string& GetId() const { return id; }
	const std::string& GetName() const { return name; }
	const std::string& GetDescription() const { return description; }

	virtual bool IsPlayer() const { return false; }
	virtual bool IsCharacter() const { return false; }
	virtual bool IsItem() const { return false; }
	virtual bool IsRoom() const { return false; }
	virtual bool CanBeTaken() const { return false; }
};

typedef std::shared_ptr<GameObject> SharedGameObjectPtr;

#endif  //!__GAMEOBJECT__H__
