#pragma once

// A Loader for objects it in the system - loads objects from the filesystem

#include <string>
#include <memory>

#include "picojson.h"

#include "Room.h"

using namespace picojson;

class Loader {

	// loads items of various types from the file system
        // only a loader for rooms is implemented at present
		
	public:
		SharedRoomPtr load_room(const std::string & filename) const;

	protected:

		bool has_string_field(picojson::value::object & obj, const std::string & fieldname) const;
		bool has_object_field(picojson::value::object & obj, const std::string & fieldname) const;

		bool load_links(const std::string & filename, const picojson::value::object & obj, SharedRoomPtr room) const;


};
