// A Loader for objects it in the system - loads objects from the filesystem
// This loader loads a whole directory of objects, and inserts them into the
// specified index

#include "DirectoryLoader.h"
#include "Index.h"

#include <string>
#include <memory>

#include <filesystem>
#include <iostream>

#include "StringUtils.h"

#include "Room.h"
#include "Loader.h"
#include "Logger.h"

bool DirectoryLoader::load_directory_of_rooms(const std::string& dirname, Index<Room>* roomIndex) const {
	Loader loader;
	Log("About to load directory : %s", dirname.c_str());

	for (const auto& entry : std::filesystem::directory_iterator(dirname)) {
		auto filePath = entry.path();
		auto filePathCstr = filePath.c_str();
		if (StringUtils::ends_with(filePathCstr, ".json")) {
			Log("Loading: %s", filePathCstr);
			SharedRoomPtr room = loader.load_room(filePathCstr);
			if (!room) {
				LogError("Cannot load room (%s)", filePathCstr);
				return false;
			}
			Log("Successfully loaded room : %s", filePathCstr);
			roomIndex->add_object(room);
		}
	}
	return true;
}

