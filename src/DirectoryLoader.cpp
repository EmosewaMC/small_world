// A Loader for objects it in the system - loads objects from the filesystem
// This loader loads a whole directory of objects, and inserts them into the
// specified index

#include "DirectoryLoader.h"
#include "Index.h"

#include <string>
#include <memory>

#include <iostream>

#include "listdir.h"
#include "string_utils.h"

#include "Room.h"
#include "Loader.h"
#include "Logger.h"

bool DirectoryLoader::load_directory_of_rooms(const std::string& dirname, Index<Room>* roomIndex) const {

	Loader loader;
	Log("Abour to load directory : %s", dirname.c_str());

	std::vector<std::string> fileNames = list_dir(dirname);

	for (const auto& entry : fileNames) {

		if (entry == "..") continue;
		if (entry == ".") continue;

		if (!ends_with(entry, ".json")) continue;

		std::string path = dirname + entry;
		Log("Loading: %s", path.c_str());

		SharedRoomPtr room = loader.load_room(path);

		if (room == nullptr) {
			LogError("Cannot load room : %s", entry.c_str());
			return false;
		}
		Log("Successfully loaded room : %s", entry.c_str());
		roomIndex->add_object(room);
	}
	return true;
}

