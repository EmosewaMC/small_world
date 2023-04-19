
#include <iostream>
#include <signal.h>
#include <future>
#include <thread>

#include "Player.h"
#include "Room.h"
#include "Index.h"
#include "DirectoryLoader.h"
#include "Logger.h"

#include "trim.h"
#include "split.h"

typedef std::shared_ptr<Room> SharedRoomPtr; 

SharedRoomPtr get_next_room(Index<Room>* index, SharedRoomPtr room, const std::string& direction) {

		const std::string& next_room_id = room->get_next_room_id(direction);

		if (next_room_id.empty()) {
			Logger::Instance().Log("There is no where to go in the %s direction", direction.c_str());
			return nullptr;
		}

		SharedRoomPtr proposed_room = index->get_object(next_room_id);

		if (proposed_room) {
			Logger::Instance().Log("There was a room proposed for %s but it does not exist in the index", direction.c_str());
			return nullptr;
		}

		return proposed_room;
}

int main() {
	auto fmt = "logs/log_%i_.txt";
	char buf[100];
	snprintf(buf, 100, fmt, time(NULL));
	Logger::Instance().Initialize(buf);
	Logger::Instance().Log("Starting the game at time %i", time(NULL));
	Logger::Instance().Flush();

	signal(SIGINT, [](int) { Logger::Instance().Shutdown(); exit(EXIT_SUCCESS); });
	auto f = std::async(std::launch::async, [=]() {
		Logger::Instance().Log("Starting the input thread");
        std::string s = "";
		std::cin >> s;
		std::cout << s << std::endl;
		return s;
    });
	Logger::Instance().Log("Creating the player");
	Player player("Player1", "Player1", "A non-descript player.  They are grey-ish"); 
	Index<Room> rooms;

	Logger::Instance().Log("Loading the rooms");
	DirectoryLoader loader;
	loader.load_directory_of_rooms("./data/rooms/", &rooms);
	
	std::string starting_room = "mrober10-room-a";
	SharedRoomPtr room = rooms.get_object(starting_room);

	Logger::Instance().Log("Getting the starting room");

	if (!room) {
		Logger::Instance().LogError("Cannot find the starting room : %s", starting_room.c_str());
		Logger::Instance().Shutdown();
		rooms.clear();
		player.clear();
		return EXIT_FAILURE;
	}

	player.set_current_room(room);
	Logger::Instance().Log("\n");

	player.look();

	std::string input_line;
	
	do {
		continue;
		std::getline(std::cin, input_line);
	 	input_line = trim(input_line);		

		if ((input_line == "q") || (input_line == "Q") || (input_line == "quit")) {
			std::cout << "bye" << std::endl;
			rooms.clear();
			player.clear();
			return EXIT_SUCCESS;
		}

		if (input_line == "look") {
			player.look();
			continue;
		}

		if (input_line.rfind("go", 0) == 0) {

			std::vector<std::string> sp = split(input_line, " ");	

			if (sp.size() == 1) {
				std::cout << "Go where?" << std::endl;
				continue;
			}

			const std::string direction = sp[1];

			std::cout << " go " << direction << std::endl;

			SharedRoomPtr current_room = player.get_current_room();

			if (current_room == nullptr) {
				std::cout << "You are standing nowhere, so can't go anywhere" << std::endl;
				continue;
			}

			SharedRoomPtr proposed_room = get_next_room(&rooms, current_room, direction);
			if (proposed_room == nullptr) {
				std::cout << "There isn't anything in that direction" << std::endl;
				continue;
			}
	
			player.set_current_room(proposed_room);
			std::cout << std::endl << std::endl;

			player.look();

			continue;

		}
		Logger::Instance().Log("I'm sorry, I don't understand that");
	} while (true);
}

