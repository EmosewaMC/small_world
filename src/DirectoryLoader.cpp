#include "DirectoryLoader.h"

#include <filesystem>

#include "Index.h"
#include "Room.h"
#include "Loader.h"
#include "Logger.h"
#include "StringUtils.h"

void DirectoryLoader::LoadDirectoryOfRooms(const std::string& dirname, Index<Room>* roomIndex) {
	LogDebug("Loading directory : %s", dirname.c_str());

	for (const auto& entry : std::filesystem::directory_iterator(dirname)) {
		auto fileName = entry.path().filename();
		auto fileNameCstr = fileName.c_str();
		if (StringUtils::EndsWith(fileName, ".json")) {
			LogDebug("Loading: %s", fileNameCstr);
			SharedRoomPtr room = Loader::Instance().load_room(entry.path());
			if (!room) {
				LogError("Cannot load room (%s). Skipping.", fileNameCstr);
				continue;
			}
			Log("Successfully loaded room : %s", fileNameCstr);
			roomIndex->add_object(room);
		}
	}
	Log("Loaded all json files in %s", dirname.c_str());
}

