
#include "Loader.h"

#include <fstream>
#include "picojson.h"
#include "PicoJsonUtils.h"
#include "Logger.h"

// loads items of various types from the file system
// here, we hand deserialize stuff from JSON in a file
// In most commerical systems, this would be done using an automatic deserializer
SharedRoomPtr Loader::load_room(const std::string& filename) const {
	// load a room from the JSON contained in filename
	// if there are errors, note these to LogError, and return nullptr
	// otherwise, return a shared_ptr to the room

	picojson::value v;
	std::ifstream file(filename);

	file >> v;

	std::string err = picojson::get_last_error();

	if (!err.empty()) {
		LogError("Error reading file : %s : %s", filename.c_str(), err.c_str());
		return nullptr;
	}

	if (!v.is<picojson::object>()) {
		LogError("Contents of file : %s are not a valid JSON object : %s", filename.c_str(), v.to_str().c_str());
		return nullptr;
	}

	// it's an object, so uses it as such	
	picojson::object& obj = v.get<picojson::object>();

	if (!PicoJsonUtils::HasField<std::string>(obj, "Id")) {
		LogError("filename : %s does not contain an Id property (or it is not a string)", filename.c_str());
		return nullptr;
	}

	if (!PicoJsonUtils::HasField<std::string>(obj, "Name")) {
		LogError("filename : %s does not contain a Name Property (or it is not a string)", filename.c_str());
		return nullptr;
	}

	if (!PicoJsonUtils::HasField<std::string>(obj, "Description")) {
		LogError("filename : %s does not contain a Description property (or it is not a string)", filename.c_str());
		return nullptr;
	}

	picojson::value vId = obj["Id"];
	picojson::value vName = obj["Name"];
	picojson::value vDesc = obj["Description"];

	SharedRoomPtr room = std::make_shared<Room>(vId.get<std::string>(), vName.get<std::string>(), vDesc.get<std::string>());

	// now load the links to other rooms, if any

	if (!PicoJsonUtils::HasField<picojson::object>(obj, "Links")) {
		LogWarning("filename : %s does not contain a Links property and may be a dead end!", filename.c_str());
		return room;  // it's fine to be a "standalone" room with no links
	}

	uint32_t loadedLinks = LoadLinks(filename, obj["Links"].get<picojson::object>(), room);

	if (loadedLinks > 0) LogError("Error loading %i links from filename : %s", loadedLinks, filename.c_str());

	return room;
}

uint32_t Loader::LoadLinks(const std::string& filename, const picojson::object& obj, SharedRoomPtr room) const {
	// load links to other rooms.  An example of using an iterator to iterate a JSON OBJECT
	uint32_t failedLinks = 0;
	for (auto link : obj) {
		const std::string& direction = link.first;
		picojson::value linked_room = link.second;
		if (!linked_room.is<std::string>()) {
			LogError("Link in filename : %s named %s is not a string", filename.c_str(), direction.c_str());
			failedLinks++;
		}
		else {
			room->AddLink(direction, linked_room.get<std::string>());
		}
	}
	return failedLinks;
}
