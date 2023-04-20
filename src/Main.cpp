
#include <signal.h>

#include <chrono>
#include <future>
#include <iostream>
#include <thread>

#include "DirectoryLoader.h"
#include "StringUtils.h"
#include "Index.h"
#include "Logger.h"
#include "Player.h"
#include "Room.h"

#define FPS 15
#define MILLISECONDS_PER_FRAME 1000 / FPS

SharedRoomPtr get_next_room(Index<Room>* index, SharedRoomPtr room, const std::string& direction) {
	const std::string& next_room_id = room->get_next_room_id(direction);
	if (next_room_id.empty()) {
		Log("There is no where to go in the %s direction", direction.c_str());
		return nullptr;
	}

	SharedRoomPtr proposed_room = index->get_object(next_room_id);
	if (!proposed_room) {
		Log("There was a room proposed for %s but it does not exist in the index",
			direction.c_str());
		return nullptr;
	}

	return proposed_room;
}

#define PlayerInputAsync                      \
  std::async(std::launch::async, [&]() {      \
    Log("Awaiting player input");             \
    std::string s = "";                       \
    std::getline(std::cin, s);                \
    Log("Exact Player input: (%s)", s.c_str()); \
    return s;                                 \
  });

void Shutdown(bool isExit = false) {
	Log("Shutting down the game");
	Logger::Instance().Shutdown();
	if (isExit) {
		exit(EXIT_SUCCESS);
	}
}

int main() {
	auto fmt = "logs/log_%i.txt";
	char buf[100];
	snprintf(buf, 100, fmt, time(NULL));
	Logger::Instance().Initialize(buf);
	Log("Starting the game at time %i", time(NULL));
	Logger::Instance().Flush();

	signal(SIGINT, [](int termSignal) { Log("Received signal %i", termSignal); Shutdown(true); });
	atexit([]() { Logger::Instance().Shutdown(); });
	Log("Creating the player");
	Player player("Player1", "Player1",
		"A non-descript player.  They are grey-ish");
	Index<Room> rooms;

	Log("Loading the rooms");
	DirectoryLoader loader;
	loader.load_directory_of_rooms("./data/rooms/", &rooms);

	std::string starting_room = "mrober10-room-a";

	Log("Getting the starting room");
	SharedRoomPtr room = rooms.get_object(starting_room);

	Log("Got the starting room");

	if (!room) {
		LogError("Cannot find the starting room : %s", starting_room.c_str());
		Logger::Instance().Shutdown();
		rooms.clear();
		player.clear();
		return EXIT_FAILURE;
	}

	player.set_current_room(room);
	Log("\n");

	player.look();

	std::string input_line;

	// Begin player input
	auto playerInput = PlayerInputAsync;

	auto currentTime = std::chrono::high_resolution_clock::now();
	while (true) {
		auto playerInputStatus = playerInput.wait_until(currentTime);
		bool playerInputReady = playerInputStatus == std::future_status::ready;
		if (playerInputReady) {
			input_line = playerInput.get();
			input_line = StringUtils::Trim(input_line);
		}
		// Lowercase for consistency
		std::transform(input_line.begin(), input_line.end(), input_line.begin(),
			::tolower);

		if (input_line == "q" || input_line == "quit" || input_line == "exit") {
			Message("bye");
			rooms.clear();
			player.clear();
			Shutdown();
			return EXIT_SUCCESS;
		}

		if (playerInputReady) {
			Log("Trimmed player input: (%s) size (%i)", input_line.c_str(), input_line.size());
			if (input_line == "look") {
				player.look();
			} else if (input_line.find("go ", 0) == 0) {
				std::vector<std::string> sp = StringUtils::Split(input_line, " \t");

				if (sp.size() <= 1) {
					Log("I need a valid direction to go in.");
				} else {
					const std::string& direction = sp.at(1);

					SharedRoomPtr current_room = player.get_current_room();

					if (!current_room) {
						LogError("You are standing nowhere, so can't go anywhere.  Shutting down game.");
						exit(EXIT_FAILURE);
					}

					SharedRoomPtr proposed_room = get_next_room(&rooms, current_room, direction);
					if (proposed_room) {
						player.set_current_room(proposed_room);
						Log("\n");
						player.look();
					} else {
						Log("There isn't anything in that direction");
					}
				}
			} else {
				Log("The command %s is not recognized", input_line.c_str());
			}
			playerInput = PlayerInputAsync;
		}
		currentTime += std::chrono::milliseconds(MILLISECONDS_PER_FRAME);
		std::this_thread::sleep_until(currentTime);
	}
}
