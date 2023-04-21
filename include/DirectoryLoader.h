#ifndef __DIRECTORYLOADER__H__
#define __DIRECTORYLOADER__H__

// A Loader for objects it in the system - loads objects from the filesystem
// This loader loads a whole directory of objects, and inserts them into the
// specified index

#include <string>

#include "Room.h"
#include "Index.h"

namespace DirectoryLoader {
	void LoadDirectoryOfRooms(const std::string& dirname, Index<Room>* index);
};

#endif  //!__DIRECTORYLOADER__H__
