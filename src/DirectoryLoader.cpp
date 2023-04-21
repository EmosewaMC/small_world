#include "DirectoryLoader.h"

#include <filesystem>

#include "Index.h"
#include "Room.h"
#include "Loader.h"
#include "Logger.h"
#include "StringUtils.h"

void DirectoryLoader::LoadDirectoryOfRooms(const std::string& dirname, Index<Room>* roomIndex) {
	Loader loader;
	Log("About to load directory : %s", dirname.c_str());

	for (const auto& entry : std::filesystem::directory_iterator(dirname)) {
		auto filePath = entry.path();
		auto filePathCstr = filePath.c_str();
		if (StringUtils::EndsWith(filePathCstr, ".json")) {
			Log("Loading: %s", filePathCstr);
			SharedRoomPtr room = loader.load_room(filePathCstr);
			if (!room) {
				LogError("Cannot load room (%s). Skipping.", filePathCstr);
				continue;
			}
			Log("Successfully loaded room : %s", filePathCstr);
			roomIndex->add_object(room);
		}
	}
	Log("Finished loading directory : %s", dirname.c_str());
}

